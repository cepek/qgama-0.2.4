/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 3 of the License, or
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
#include <QtXmlPatterns>

#include "solvenetwork.h"
#include "../exception.h"

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


/* ===============================================================================================================*/
/**
  *
  */
SolveNetwork::SolveNetwork(const QString &stream, AdjustmentSetting *setting, Document *doc) :
    inputXmlStream(stream),
    as(setting),
    document(doc)
{
    connect(this, SIGNAL(terminated()), this, SLOT(onTerminate()));
}


/* ===============================================================================================================*/
/**
  *
  */
void SolveNetwork::run() {
    QString outputXmlStream;
    QString outputTxtStream;
    QString outputHtmlStream;

    try {
        solveNetwork_(outputXmlStream, outputTxtStream, outputHtmlStream);
        emit solved(outputXmlStream, outputTxtStream, outputHtmlStream, document, as);
    }
    catch (Exception e) {
        emit solvingFailed(e.text);
    }

    exit();
}


/* ===============================================================================================================*/
/**
  *
  */
void SolveNetwork::onTerminate()
{
    delete this;
}


/* ===============================================================================================================*/
/**
  *
  */
void SolveNetwork::solveNetwork_(QString &outputXmlStream, QString &outputTxtStream, QString &outputHtmlStream)
{
    qDebug() << "SolveNetwork::solveNetwork_() - START";

    Q_ASSERT(as!=0 && "as pointer is 0!");

    // get adjustment parameters
    string description;
    string argv_algo      = as->getAlgorithm().toStdString();
    string argv_lang      = as->getLanguage().toStdString();
    string argv_enc       = as->getEncoding().toStdString();
    string argv_angles    = as->getAngles().toStdString();
    string argv_ellipsoid = as->getEllipsoid().toStdString();
    string argv_latitude  = as->getLatitude().toStdString();
    int argv_covband      = as->getCovband().toInt();
    QString formats    = as->getOutput();
    bool argv_txt      = formats.contains("txt");
    bool argv_xml      = formats.contains("xml");
    bool argv_html     = formats.contains("html");

    /*
    bool argv_obs      = false;
    string argv_obsout = "";
    */

    // rest of initializations
    bool correction_to_ellipsoid = false;
    GNU_gama::Ellipsoid el;
    double latitude = M_PI/4.0;
    string errorOutput = "";

    if      ("en"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'en'"; set_gama_language(en); }
    else if ("ca"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'ca'"; set_gama_language(ca); }
    else if ("cs"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'cz'"; set_gama_language(cz); }
    else if ("cz"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'cz'"; set_gama_language(cz); }
    else if ("du"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'du'"; set_gama_language(du); }
    else if ("fi"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'fi'"; set_gama_language(fi); }
    else if ("fr"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'fr'"; set_gama_language(fr); }
    else if ("hu"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'hu'"; set_gama_language(hu); }
    else if ("ru"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'ru'"; set_gama_language(ru); }
    else if ("ua"==argv_lang) { qDebug() << "solveNetwork_() - language set to 'ua'"; set_gama_language(ua); }

    qDebug() << "solveNetwork_() - parameters initialized";

    // create the network
    LocalNetwork* IS;

    qDebug() << "solveNetwork_() - network allocated";

    // initialize output stream
    ostream* txt_output = 0;
    ostringstream txt_output2;
    if (argv_txt)
        txt_output = &txt_output2;
    GNU_gama::OutStream cout(txt_output);

    qDebug() << "solveNetwork_() - output stream initialized";

    // set encoding
    if ("utf-8"==argv_enc)
      cout.set_encoding(OutStream::utf_8);
    else if ("iso-8859-2"==argv_enc)
      cout.set_encoding(OutStream::iso_8859_2);
    else if ("iso-8859-2-flat"==argv_enc)
      cout.set_encoding(OutStream::iso_8859_2_flat);
    else if ("cp-1250"==argv_enc)
      cout.set_encoding(OutStream::cp_1250);
    else if ("cp-1251"==argv_enc)
      cout.set_encoding(OutStream::cp_1251);

    qDebug() << "solveNetwork_() - encoding set";

    try {
        try {
            // set algorithm
            if      ("svd"==argv_algo) IS = new LocalNetwork_svd;
            else if ("gso"==argv_algo) IS = new LocalNetwork_gso;
            else if ("cholesky"==argv_algo) IS = new LocalNetwork_chol;
            else if ("envelope"==argv_algo) IS = new LocalNetwork_env;

            qDebug() << "solveNetwork_() - algorithm set";

            // set angles
            if ("400"==argv_angles)
                IS->set_gons();
            else if ("360"==argv_angles)
                IS->set_degrees();

            qDebug() << "solveNetwork_() - angles set";

            // set covband
            if (argv_covband==-1 || argv_covband>=0)
                IS->set_xml_covband(argv_covband);

            qDebug() << "solveNetwork_() - covband set";
        }

        catch (...) {
            throw GaMaLib::Exception(T_GaMa_exception_1);
        }

        // set latitude
        if (""!=argv_latitude) {
            latitude = atof(argv_latitude.c_str()) * M_PI / (IS->gons() ? 200 : 180);
            correction_to_ellipsoid = true;

            qDebug() << "solveNetwork_() - latitude correction set";
        }

        // set ellipsoid
        GNU_gama::set(&el, GNU_gama::ellipsoid_wgs84);

        if (""!=argv_ellipsoid) {
            gama_ellipsoid gama_el = ellipsoid(argv_ellipsoid.c_str());
            correction_to_ellipsoid = true;

            qDebug() << "solveNetwork_() - ellipsoid correction set";
        }

        emit label(1, tr("Adjustment parameters initialized."));

        // set input XML stream
        istringstream soubor(inputXmlStream.toStdString());

        qDebug() << "solveNetwork_() - input xml stream set";

        // start parsing it
        qDebug() << "solveNetwork_() - starting parsing it";
        emit label(2, tr("Starting parsing the network."));
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
                throw; //Exception("Unexpected failure during parsing the network's XML.");         // should be added later ???
            }
        }
    }

    catch (const GaMaLib::ParserException& v) {
        throw Exception(QString(T_GaMa_exception_2a) + "\n\n" + QString(T_GaMa_exception_2b) + QString::number(v.line) + " : " + QString::fromStdString(v.text));
    }
    catch (const GaMaLib::Exception& v) {
        throw Exception(QString(T_GaMa_exception_2a) + "\n" + "\n***** " + QString::fromStdString(v.text) + "\n\n");
    }
    catch (...) {
        errorOutput += "\n";
        errorOutput += T_GaMa_exception_2a;
        errorOutput += "\n\n";

        throw Exception("Unexpected failure during the network's inicialization!");
    }

    // starting adjusting
    qDebug() << "solveNetwork_() - starting adjusting";
    emit label(3, tr("Starting adjusting..."));

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

        try {
            if (!GaMaConsistent(IS->PD))
            {
                cout << T_GaMa_inconsistent_coordinates_and_angles << "\n\n\n";
            }

            qDebug() << "solveNetwork_() - Calculation of approximate coordinates";
            emit label(4, tr("Calculation of approximate coordinates."));

            Acord acord(IS->PD, IS->OD);
            acord.execute();

            ReducedObservationsText(IS,&(acord.RO), cout);

            if (correction_to_ellipsoid)
            {
                qDebug() << "solveNetwork_() - calculation of corrections to ellipsoid";

                ReduceToEllipsoid reduce_to_el(IS->PD, IS->OD, el, latitude);
                reduce_to_el.execute();
                ReducedObservationsToEllipsoidText(IS, reduce_to_el.getMap(), cout);
            }

            ApproximateCoordinates(&acord, cout);
        }
        catch(GaMaLib::Exception e)
        {
            errorOutput += e.text;
            throw Exception(QString::fromStdString(errorOutput));
        }
        catch(...)
        {
            errorOutput += "Gama / Acord: approximate coordinates failed\n\n";
            throw Exception(QString::fromStdString(errorOutput));
        }

        // cerr << IS->PD << IS->OD << "\n\n";

        if (IS->sum_points() == 0 || IS->sum_unknowns() == 0)
        {
            throw Exception(T_GaMa_No_network_points_defined);
        }
        else
        {
            if (IS->huge_abs_terms())
            {
                qDebug() << "solveNetwork_() - outlying the huge absolute terms";

                OutlyingAbsoluteTerms(IS, cout);
                IS->remove_huge_abs_terms();
                cout << T_GaMa_Observatios_with_outlying_absolute_terms_removed
                << "\n\n\n";
            }

            if (!IS->connected_network())
                cout  << T_GaMa_network_not_connected << "\n\n\n";

            qDebug() << "solveNetwork_() - adding the description";

            NetworkDescription(description, cout);

            if (GeneralParameters(IS, cout))
            {
                int iterace = 0;

                emit label(4, tr("Adjusting unknowns."));

                do
                {
                    qDebug() << "solveNetwork_() - calculating " << iterace+1 << " iteration";

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

                    qDebug() << "solveNetwork_() - adjusting unknowns";

                    AdjustedUnknowns(IS, cout);
                }
                while (TestLinearization(IS, cout) && iterace < 3);

                qDebug() << "solveNetwork_() - calculation of error ellipses";
                emit label(5, tr("Calculation of error ellipses."));

                ErrorEllipses        (IS, cout);

                qDebug() << "solveNetwork_() - adjusting observations";
                emit label(6, tr("Calculation of adjusted observations."));

                AdjustedObservations (IS, cout);

                qDebug() << "solveNetwork_() - calculating residuals and analyzing the observations";
                emit label(7, tr("Calculation of residuals and analyzing the observations."));

                ResidualsObservations(IS, cout);
            }

            /*
            if (argv_obs)
            {
                ostringstream opr(argv_obsout);
                IS->project_equations(opr);
            }
            */

            if (argv_txt)
            {
                qDebug() << "solveNetwork_() - outputing txt stream";
                emit label(8, tr("Outputing results in TXT format."));

                outputTxtStream = QString::fromStdString(txt_output2.str());
            }

            if (argv_xml || argv_html)
            {
                qDebug() << "solveNetwork_() - outputing xml stream";
                emit label(9, tr("Outputing results in XML format."));

                IS->set_gons();

                GNU_gama::LocalNetworkXML xml(IS);
                xml.description = description;
                ostringstream xml_output;
                xml.write(xml_output);
                qDebug() << "GamaLocal - outputing xml stream";
                outputXmlStream = QString::fromStdString(xml_output.str());

                if (argv_html)
                {
                    qDebug() << "solveNetwork_() - outputing html stream";
                    emit label(10, tr("Outputing results in HTML format."));

                    QXmlQuery query(QXmlQuery::XSLT20);
                    query.setFocus(outputXmlStream);
                    QFile xslFile(QString(":/xml/gama-local-adjustment.xsl"));
                    xslFile.open(QIODevice::ReadOnly);
                    const QString xslText(QString::fromUtf8(xslFile.readAll()));
                    query.setQuery(xslText);
                    query.evaluateTo(&outputHtmlStream);
                }
            }
        }

        emit label(11, tr("Adjustment succesfully completed."));
        delete IS;
        return;
    }
    catch (const GaMaLib::Exception& V)
    {
        throw Exception(QString(T_GaMa_solution_ended_with_error) + "\n\n" + "****** " + QString::fromStdString(V.text));
    }
    catch(const GNU_gama::Exception::adjustment& choldec)
    {
        throw Exception(QString(T_GaMa_solution_ended_with_error) + "\n\n" + "****** " + QString::fromStdString(choldec.str));
    }
    catch(...)
    {
        throw Exception(QString(T_GaMa_internal_program_error));
    }

    Q_ASSERT(false && "unreachable code");
}
