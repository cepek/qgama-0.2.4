/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 2 of the License, or
**    (at your option) any later version.
**
**    This library is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this library; if not, write to the Free Software
**    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
****************************************************************************/

#include <QtGui>

#include "gamalocal.h"

#include <cstring>
#include <gnu_gama/outstream.h>
#include <gnu_gama/version.h>
#include <gnu_gama/intfloat.h>
#include <gnu_gama/xml/localnetwork.h>
#include <gamalib/language.h>
#include <gamalib/local/gamadata.h>
#include <gamalib/xml/gkfparser.h>
#include <gamalib/local/network_svd.h>
#include <gamalib/local/network_gso.h>
#include <gamalib/local/network_chol.h>
#include <gamalib/local/network_env.h>
#include <gamalib/local/acord.h>
#include <gamalib/local/results/text/approximate_coordinates.h>
#include <gamalib/local/results/text/network_description.h>
#include <gamalib/local/results/text/general_parameters.h>
#include <gamalib/local/results/text/fixed_points.h>
#include <gamalib/local/results/text/adjusted_observations.h>
#include <gamalib/local/results/text/adjusted_unknowns.h>
#include <gamalib/local/results/text/outlying_abs_terms.h>
#include <gamalib/local/results/text/reduced_observations.h>
#include <gamalib/local/results/text/reduced_observations_to_ellipsoid.h>
#include <gamalib/local/results/text/residuals_observations.h>
#include <gamalib/local/results/text/error_ellipses.h>
#include <gamalib/local/results/text/test_linearization.h>

using namespace QGamaCore;
using namespace GaMaLib;
using namespace std;
using namespace GNU_gama;


int GamaLocal::solveNetwork(const QString &network, AdjustmentSetting *as)
{
    qDebug() << "GamaLocal::solveNetwork() - START";

    // declarations
    string description;
    const char* argv_1 = 0;
    const char* argv_algo = 0;
    const char* argv_lang = 0;
    const char* argv_enc  = 0;
    const char* argv_angles = 0;
    const char* argv_ellipsoid = 0;
    const char* argv_latitude = 0;
    const char* argv_txtout = 0;
    const char* argv_xmlout = 0;
    int argv_covband;

    // definitions
    bool correction_to_ellipsoid = false;
    GNU_gama::Ellipsoid el;
    double latitude = M_PI/4.0;

    // initializations
    argv_algo = as->getAlgorithm().toAscii();
    argv_lang = as->getLanguage().toAscii();
    argv_enc = as->getEncoding().toAscii();
    argv_angles = as->getAngles().toAscii();
    if (!as->getEllipsoid().isEmpty())
        argv_ellipsoid = as->getEllipsoid().toAscii();
    if (!as->getLatitude().isEmpty())
        argv_latitude = as->getLatitude().toAscii();
    argv_txtout = "results.txt";
    argv_xmlout = "results.xml";
    argv_covband = as->getCovband().toInt();
    if      (!strcmp("en", argv_lang)) set_gama_language(en);
    else if (!strcmp("ca", argv_lang)) set_gama_language(ca);
    else if (!strcmp("cs", argv_lang)) set_gama_language(cz);
    else if (!strcmp("cz", argv_lang)) set_gama_language(cz);
    else if (!strcmp("du", argv_lang)) set_gama_language(du);
    else if (!strcmp("fi", argv_lang)) set_gama_language(fi);
    else if (!strcmp("fr", argv_lang)) set_gama_language(fr);
    else if (!strcmp("hu", argv_lang)) set_gama_language(hu);
    else if (!strcmp("ru", argv_lang)) set_gama_language(ru);
    else if (!strcmp("ua", argv_lang)) set_gama_language(ua);
    argv_1 = network.toAscii();

    qDebug() << "GamaLocal - definice nastaveny";

    // create the network
    LocalNetwork* IS;
    ostream* output = 0;

    ofstream fcout;
    if (argv_txtout)
        if (!strcmp(argv_txtout, "-")) {
            output = &std::cout;
        }
        else {
            fcout.open(argv_txtout);
            output = &fcout;
        }

    GNU_gama::OutStream cout(output);

    // set encoding
    if (!strcmp("utf-8", argv_enc))
      cout.set_encoding(OutStream::utf_8);
    else if (!strcmp("iso-8859-2", argv_enc))
      cout.set_encoding(OutStream::iso_8859_2);
    else if (!strcmp("iso-8859-2-flat", argv_enc))
      cout.set_encoding(OutStream::iso_8859_2_flat);
    else if (!strcmp("cp-1250", argv_enc))
      cout.set_encoding(OutStream::cp_1250);
    else if (!strcmp("cp-1251", argv_enc))
      cout.set_encoding(OutStream::cp_1251);

    qDebug() << "GamaLocal - sit vytvorena a dalsi veci nastaveny";

    try {

        try {
            // set algorithm
            if (     !strcmp("svd",      argv_algo)) IS = new LocalNetwork_svd;
            else if (!strcmp("gso",      argv_algo)) IS = new LocalNetwork_gso;
            else if (!strcmp("cholesky", argv_algo)) IS = new LocalNetwork_chol;
            else if (!strcmp("envelope", argv_algo)) IS = new LocalNetwork_env;

            // set angles
            if (!strcmp("400", argv_angles))
                IS->set_gons();
            else if (!strcmp("360", argv_angles))
                IS->set_degrees();

            // set covband
            qDebug() << "!!!" << argv_covband;
            IS->set_xml_covband(argv_covband);

            qDebug() << "GamaLocal - algoritmus a uhly nastaveny";
        }

        catch (...) {
            throw
            GaMaLib::Exception(T_GaMa_exception_1);
        }

        if (argv_latitude) {
            latitude = atof(argv_latitude) * M_PI / (IS->gons() ? 200 : 180);
            correction_to_ellipsoid = true;
        }

        GNU_gama::set(&el, GNU_gama::ellipsoid_wgs84);

        if (argv_ellipsoid) {
            gama_ellipsoid gama_el = ellipsoid(argv_ellipsoid);
            correction_to_ellipsoid = true;
        }

        ifstream soubor(argv_1);

        {
            GKFparser gkf(IS->PD, IS->OD);
            try {
                char c;
                int  n, konec = 0;
                string radek;
                do {
                    radek = "";
                    n     = 0;
                    while (soubor.get(c)) {
                        radek += c;
                        n++;
                        if (c == '\n') break;
                    }
                    if (!soubor) konec = 1;

                    gkf.xml_parse(radek.c_str(), n, konec);
                } while (!konec);

                IS->apriori_m_0(gkf.m0_apr );
                IS->conf_pr    (gkf.konf_pr);
                IS->tol_abs    (gkf.tol_abs);

                IS->update_constrained_coordinates(gkf.update_constr);

                if (gkf.typ_m0_apriorni)
                    IS->set_m_0_apriori();
                else
                    IS->set_m_0_aposteriori();

                description = gkf.description;
                IS->epoch = gkf.epoch;
            }
            catch (...)
            {
                throw;         // should be added later ???
            }
        }
    }

    catch (const GaMaLib::ParserException& v) {
        cerr << "\n" << T_GaMa_exception_2a << "\n\n"
             << T_GaMa_exception_2b << v.line << " : " << v.text << endl;
        return 3;
    }
    catch (const GaMaLib::Exception& v) {
        cerr << "\n" <<T_GaMa_exception_2a << "\n"
             << "\n***** " << v.text << "\n\n";
        return 2;
    }
    catch (...) {
        cerr << "\n" << T_GaMa_exception_2a << "\n\n";
        throw;
        // return 3;
    }


    try {
      {
        cout << T_GaMa_Adjustment_of_geodetic_network << "        "
             << T_GaMa_version << GNU_gama::GNU_gama_version
             << "-" << IS->algorithm()
             << " / " << GNU_gama::GNU_gama_compiler << "\n"
             << underline(T_GaMa_Adjustment_of_geodetic_network, '*') << "\n"
             << "http://www.gnu.org/software/gama/\n\n\n";
      }

      if (IS->PD.empty())
        throw GaMaLib::Exception(T_GaMa_No_points_available);

      if (IS->OD.clusters.empty())
        throw GaMaLib::Exception(T_GaMa_No_observations_available);

      try
        {
          if (!GaMaConsistent(IS->PD))
            {
              cout << T_GaMa_inconsistent_coordinates_and_angles << "\n\n\n";
            }
          Acord acord(IS->PD, IS->OD);
          acord.execute();
          ReducedObservationsText(IS,&(acord.RO), cout);

          if (correction_to_ellipsoid)
          {
              ReduceToEllipsoid reduce_to_el(IS->PD, IS->OD, el, latitude);
              reduce_to_el.execute();
              ReducedObservationsToEllipsoidText(IS, reduce_to_el.getMap(), cout);
          }

          ApproximateCoordinates(&acord, cout);

        }
      catch(GaMaLib::Exception e)
        {
          cerr << e.text << endl;
          return 1;
        }
      catch(...)
        {
          cerr << "Gama / Acord: approximate coordinates failed\n\n";
          return 1;
        }

      // cerr << IS->PD << IS->OD << "\n\n";

      if (IS->sum_points() == 0 || IS->sum_unknowns() == 0)
        {
          throw GaMaLib::Exception(T_GaMa_No_network_points_defined);
        }
      else
        {
          if (IS->huge_abs_terms())
            {
              OutlyingAbsoluteTerms(IS, cout);
              IS->remove_huge_abs_terms();
              cout << T_GaMa_Observatios_with_outlying_absolute_terms_removed
                   << "\n\n\n";
            }

          if (!IS->connected_network())
            cout  << T_GaMa_network_not_connected << "\n\n\n";

          NetworkDescription(description, cout);
          if (GeneralParameters(IS, cout))
            {
              int iterace = 0;
              do
                {
                  if(++iterace > 1)
                    {
                      cout << "\n         ******  "
                           << iterace << T_GaMa_adjustment_iteration
                           << "  ******\n\n"
                           << T_GaMa_Approximate_coordinates_replaced << "\n"
                           << underline(T_GaMa_Approximate_coordinates_replaced,
                                        '*') << "\n\n\n";

                      IS->refine_approx();
                      GeneralParameters(IS, cout);
                    }
                  FixedPoints     (IS, cout);
                  AdjustedUnknowns(IS, cout);
                }
              while (TestLinearization(IS, cout) && iterace < 3);

              ErrorEllipses        (IS, cout);
              AdjustedObservations (IS, cout);
              ResidualsObservations(IS, cout);

            }

          /*
          if (argv_obsout)
            {
              ofstream opr(argv_obsout);
              IS->project_equations(opr);
            }
            */

          // implicit output
          if (!argv_txtout && !argv_xmlout) argv_xmlout = "-";

          if (argv_xmlout)
            {
              IS->set_gons();

              GNU_gama::LocalNetworkXML xml(IS);
              xml.description = description;

              if (!strcmp(argv_xmlout, "-"))
                {
                  xml.write(std::cout);
                }
              else
                {
                  ofstream file(argv_xmlout);
                  xml.write(file);
              }
            }

        }

      delete IS;
      return 0;

    }
    catch (const GaMaLib::Exception& V)
      {
        cout << "\n" << T_GaMa_solution_ended_with_error << "\n\n"
             << "****** " << V.text << "\n\n";
      }
    catch(const GNU_gama::Exception::adjustment& choldec)
      {
        cout << "\n" << T_GaMa_solution_ended_with_error << "\n\n"
             << "****** " << choldec.str << "\n\n";
      }
    catch(...)
      {
        cout << "\n" << T_GaMa_internal_program_error << "\n\n";
      }

    return 1;
}
