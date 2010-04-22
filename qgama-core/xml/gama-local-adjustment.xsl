<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  
  <!-- Output will be in HTML, encoding in UTF-8 -->
  <xsl:output indent="yes" method="html" encoding="utf-8"/>


  <!-- Root document element -->
  <xsl:template match="/">
    <html>
      <head>
	<!--
	<style type="text/css">
	</style>
	-->
	<script language="JavaScript">
	  function changeDisplay(el) {
 	  var el=document.getElementById(el).style;
	  el.display=(el.display=='none')?'block':'none';
	  }
	</script>
      </head>
      <body>
        <xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>


  <!-- Section "Network's decription"-->
  <xsl:template match="description">
    <h4 onclick="changeDisplay('description')">1. Network's description:</h4>
    <div id="description" style="display:none">
      <xsl:call-template name="nl2br">
	<xsl:with-param name="where" select="text()" />
      </xsl:call-template>
    </div>
  </xsl:template>


  <!-- Section "Network's general parameters" -->
  <xsl:template match="network-general-parameters">
    <h4 onclick="changeDisplay('parameters')">2. Network's general parameters:</h4>
    <div id="parameters" style="display:none">
      <table>
	<xsl:for-each select="@*">
	  <tr>
	    <td><xsl:value-of select="name()"/>:</td>
	    <td><xsl:value-of select="."/></td>
	  </tr>
	</xsl:for-each>
      </table>
    </div>
  </xsl:template>


  <!-- Section "Network processing summary -->
  <xsl:template match="network-processing-summary">
    <h4 onclick="changeDisplay('summary')">3. Network processing summary</h4>
    <div id="summary" style="display:none">
      <xsl:apply-templates />
    </div>
  </xsl:template>

  
  <!-- Subsection "Coordinates summary" -->
  <xsl:template match="coordinates-summary">
    <h5 onclick="changeDisplay('coordinates-summary')">3.1. Coordinates summary</h5>
    <div id="coordinates-summary" style="display:none">
      <table border="1">
	<tr>
	  <th>Coordinates</th>
	  <th>xyz</th>
	  <th>xy</th>
	  <th>z</th>
	</tr>
	<tr>
	  <td>Adjusted</td>
	  <td><xsl:value-of select="coordinates-summary-adjusted/count-xyz" /></td>
	  <td><xsl:value-of select="coordinates-summary-adjusted/count-xy" /></td>
	  <td><xsl:value-of select="coordinates-summary-adjusted/count-z" /></td>
	</tr>
	<tr>
	  <td>Constrained</td>
	  <td><xsl:value-of select="coordinates-summary-constrained/count-xyz" /></td>
	  <td><xsl:value-of select="coordinates-summary-constrained/count-xy" /></td>
	  <td><xsl:value-of select="coordinates-summary-constrained/count-z" /></td>
	</tr>
	<tr>
	  <td>Fixed</td>
	  <td><xsl:value-of select="coordinates-summary-fixed/count-xyz" /></td>
	  <td><xsl:value-of select="coordinates-summary-fixed/count-xy" /></td>
	  <td><xsl:value-of select="coordinates-summary-fixed/count-z" /></td>
	</tr>
      </table>
    </div>
  </xsl:template>


  <!-- Subsection "Observations summary" -->
  <xsl:template match="observations-summary">
    <h5 onclick="changeDisplay('observations-summary')">3.2. Observations summary</h5>
    <div id="observations-summary" style="display:none">
      <table border="1">
	<tr>
	  <th>Type of observation</th>
	  <th>Number</th>
	</tr>
	<tr>
	  <td>Distances</td>
	  <td><xsl:value-of select="distances" /></td>
	</tr>
	<tr>
	  <td>Directions</td>
	  <td><xsl:value-of select="directions" /></td>
	</tr>
	<tr>
	  <td>Angles</td>
	  <td><xsl:value-of select="angles" /></td>
	</tr>
	<tr>
	  <td>XYZ coordinates</td>
	  <td><xsl:value-of select="xyz-coords" /></td>
	</tr>
	<tr>
	  <td>Height differences</td>
	  <td><xsl:value-of select="h-diffs" /></td>
	</tr>
	<tr>
	  <td>Zenith angles</td>
	  <td><xsl:value-of select="z-angles" /></td>
	</tr>
	<tr>
	  <td>Slope distances</td>
	  <td><xsl:value-of select="s-dists" /></td>
	</tr>
	<tr>
	  <td>Vectors</td>
	  <td><xsl:value-of select="vectors" /></td>
	</tr>
      </table>
    </div>
  </xsl:template>


  <!-- Subsection "Project equations" -->
  <xsl:template match="project-equations">
    <h5 onclick="changeDisplay('project-equations')">3.3. Project equations</h5>
    <div id="project-equations" style="display:none">
      <table border="1">
	<tr>
	  <td>Number of project equations</td>
	  <td><xsl:value-of select="equations" /></td>
	</tr>
	<tr>
	  <td>Number of unknowns</td>
	  <td><xsl:value-of select="unknowns" /></td>
	</tr>
	<tr>
	  <td>Degrees of freedom</td>
	  <td><xsl:value-of select="degrees-of-freedom" /></td>
	</tr>
	<tr>
	  <td>Network defect</td>
	  <td><xsl:value-of select="defect" /></td>
	</tr>
	<tr>
	  <td>Sum of squares</td>
	  <td><xsl:value-of select="sum-of-squares" /></td>
	</tr>
	<tr>
	  <xsl:choose>
	    <xsl:when test="./connected-network">
	      <td><b>Connected network</b></td>
	    </xsl:when>
	    <xsl:when test="./disconnected-network">
	      <td><b>Disconnected network</b></td>
	    </xsl:when>
	  </xsl:choose>
	  <td></td>
	</tr>
      </table>
    </div>
  </xsl:template>


  <!-- Subsection "Standard deviation" -->
  <xsl:template match="standard-deviation">
    <h5 onclick="changeDisplay('standard-deviation')">3.4. Standard deviation</h5>
    <div id="standard-deviation" style="display:none">
      <table border="1">
	<tr>
	  <td>m0 apriori</td>
	  <td><xsl:value-of select="apriori" /></td>
	</tr>
	<tr>
	  <td>m0' aposteriori</td>
	  <td><xsl:value-of select="aposteriori" /></td>
	</tr>
	<tr>
	  <td>Used</td>
	  <td><xsl:value-of select="used" /></td>
	</tr>
	<tr>
	  <td>Confidence level:</td>
	  <td><xsl:value-of select="probability" /></td>
	</tr>
	<tr>
	  <td>Ratio m0 apriori / m0' aposteriori</td>
	  <td><xsl:value-of select="ratio" /></td>
	</tr>
	<tr>
	  <td>Lower bound of 95% interval</td>
	  <td><xsl:value-of select="lower" /></td>
	</tr>
	<tr>
	  <td>Upper bound of 95% interval</td>
	  <td><xsl:value-of select="upper" /></td>
	</tr>
	<tr>
	  <xsl:choose>
	    <xsl:when test="./passed">
	      <td><b>Passed</b></td>
	    </xsl:when>
	    <xsl:when test="./failed">
	      <td><b>Failed</b></td>
	    </xsl:when>
	  </xsl:choose>
	  <td></td>
	</tr>
	<tr>
	  <td>Confidence scale</td>
	  <td><xsl:value-of select="confidence-scale" /></td>
	</tr>
      </table>
    </div>
  </xsl:template>


  <!-- Section "Coordinates" -->
  <xsl:template match="coordinates">
    <h4 onclick="changeDisplay('coordinates')">4. Coordinates</h4>
    <div id="coordinates" style="display:none">
      <h5 onclick="changeDisplay('fixed-points')">4.1. Fixed points</h5>
      <div id="fixed-points" style="display:none">
	<xsl:apply-templates select="fixed" />
      </div>

      <h5 onclick="changeDisplay('adjusted-coordinates')">4.2. Adjusted coordinates</h5>
      <div id="adjusted-coordinates" style="display:none">
	<xsl:call-template name="printAdjustedCoordinates" />
      </div>

      <h5 onclick="changeDisplay('orientation-shifts')">4.3. Orientation shifts</h5>
      <div id="orientation-shifts" style="display:none">
	<xsl:apply-templates select="orientation-shifts" />
      </div>
      
      <h5 onclick="changeDisplay('covariance-matrix')">4.4. Covariance matrix</h5>
      <div id="covariance-matrix" style="display:none">
	<xsl:apply-templates select="cov-mat" />
      </div>
    </div>
  </xsl:template>


  <!-- Template for printing orientation shifts -->
  <xsl:template match="orientation-shifts">
    <table border="1">
      <thead>
	<tr>
	  <th>Standpoint</th>
	  <th>Original index</th>
	  <th>Approximate value [g]</th>
	  <th>Correction [g]</th>
	  <th>Adjusted value [g]</th>
	</tr>
      </thead>
      <tbody>
	<xsl:for-each select="./*">
	  <xsl:variable name="id" select="position() + count(//coordinates/adjusted/point/*[name(.)!='id'])" />
	  <tr>
	    <td>
	      <xsl:value-of select="./id" />
	    </td>
	    <td>
	      <xsl:value-of select="//coordinates/original-index/ind[$id]" />
	    </td>
	    <td>
	      <xsl:value-of select="./approx" />
	    </td>
	    <td>
	      <!-- <xsl:value-of select="format-number(./approx - ./adj, '0.000000')" /> -->
	      <xsl:value-of select="./approx - ./adj" />
	    </td>
	    <td>
	      <xsl:value-of select="./adj" />
	    </td>
	  </tr>
	</xsl:for-each>
      </tbody>
    </table>
  </xsl:template>


  <!-- Subsection "Fixed Points" -->
  <xsl:template match="fixed">
    <table border="1">
      <thead>
	<tr>
	  <th>
	    Point
	  </th>
	  <xsl:variable name="num" select="count(./point[name(.) != 'id'])" />
	  <xsl:choose>
	    <xsl:when test="$num = 1">
	      <th>Z</th>
	    </xsl:when>
	    <xsl:when test="$num = 2">
	      <th>X</th>
	      <th>Y</th>
	    </xsl:when>
	    <xsl:when test="$num = 3">
	      <th>X</th>
	      <th>Y</th>
	      <th>Z</th>
	    </xsl:when>
	  </xsl:choose>
	</tr>
      </thead>
    <tbody>
      <xsl:for-each select="./*">
	  <tr>
	    <xsl:for-each select="./*">
	      <td>
		<xsl:value-of select="." />
	      </td>
	    </xsl:for-each>
	  </tr>
	</xsl:for-each>
      </tbody>
    </table>
  </xsl:template>



  <!-- Template for printing adjusted coordinates -->
  <xsl:template name="printAdjustedCoordinates">
    <table border="1">
      <thead>
	<tr>
	  <th>Point number</th>
	  <th>Original index</th>
	  <th>Coord</th>
	  <th>Approximate</th>
	  <th>Correction</th>
	  <th>Adjusted</th>
	</tr>
      </thead>
      <tbody>
	<xsl:for-each select="//coordinates/approximate/point/id">
	  <xsl:variable name="pointId" select="." />
	  <xsl:variable name="someNodeWithResults" select="//coordinates/approximate/point[id/text()=$pointId]" />
	  <xsl:variable name="coordsCount" select="count($someNodeWithResults/*[name(.) != 'id'])" />
	  <xsl:variable name="id" select="2 * position() - 1" />

	  <tr>
	    <td rowspan="{$coordsCount}">
	      <xsl:value-of select="." />
	    </td>
	    
	    <xsl:call-template name="printAdjustedCoordinateSingleCoordinate">
	      <xsl:with-param name="pointId" select="$pointId" />
	      <xsl:with-param name="coord" select="$someNodeWithResults/*[name(.) != 'id'][1]" />
	      <xsl:with-param name="id" select="$id" />
	    </xsl:call-template>
	  </tr>
	  <xsl:for-each select="$someNodeWithResults/*[(name(.) != 'id') and (position() &gt; 2)]">
	    <tr>
	      <xsl:call-template name="printAdjustedCoordinateSingleCoordinate">
		<xsl:with-param name="pointId" select="$pointId" />
		<xsl:with-param name="coord" select="." />
		<xsl:with-param name="id" select="$id + position()" />
	      </xsl:call-template>
	    </tr>
	  </xsl:for-each>
	</xsl:for-each>
      </tbody>
    </table>
  </xsl:template>


  <!-- Template for printing single coordinate of adjusted point -->
  <xsl:template name="printAdjustedCoordinateSingleCoordinate">
    <xsl:param name="pointId" />
    <xsl:param name="coord" />
    <xsl:param name="id" />

    <xsl:variable name="coordName" select="name($coord)" />
    <xsl:variable name="approximateNode" select="//coordinates/approximate/point[id/text()=$pointId]" />
    <xsl:variable name="adjustedNode" select="//coordinates/adjusted/point[id/text()=$pointId]" />
    <xsl:variable name="originalIndex" select="//coordinates/original-index/ind[$id]" />
    
    <td>
      <xsl:value-of select="$originalIndex" />
    </td>
    <td>
      <xsl:value-of select="$coordName" />
    </td>
    <td>
      <!--<xsl:value-of select="format-number(round(100000*$approximateNode/*[name()=$coordName]) div 100000, '#.00000')" />-->
      <xsl:value-of select="round(100000*$approximateNode/*[name()=$coordName]) div 100000" />
    </td>
    <td>
      <!--<xsl:value-of select="format-number(round(100000*($approximateNode/*[name()=$coordName]-$adjustedNode/*[name()=$coordName])) div 100000, '0.00000')" />-->
      <xsl:value-of select="round(100000*($approximateNode/*[name()=$coordName]-$adjustedNode/*[name()=$coordName])) div 100000" />
    </td>
    <td>
      <!--<xsl:value-of select="format-number(round(100000*$adjustedNode/*[name()=$coordName]) div 100000, '#.00000')" />-->
      <xsl:value-of select="round(100000*$adjustedNode/*[name()=$coordName]) div 100000" />
    </td>
  </xsl:template>
  
  
  <!-- Template for printing covariation matrix -->
  <xsl:template match="cov-mat">
    <dl>
      <dt>Dimension</dt>
      <dd><xsl:value-of select="dim" /></dd>
      <dt>Bands</dt>
      <dd><xsl:value-of select="band" /></dd>
    </dl>
    <table border="1">
      <xsl:call-template name="printCovariationMatrix">
	<xsl:with-param name="matrix" select="." />
	<xsl:with-param name="dataIndex" select="1" />
	<xsl:with-param name="dimension" select="dim" />
	<xsl:with-param name="rowLength" select="dim" />
	<xsl:with-param name="band" select="band" />
	<xsl:with-param name="row" select="1" />
      </xsl:call-template>
    </table>
  </xsl:template>

 
  <!-- Template for printing variance-covariance matrix -->
  <xsl:template name="printCovariationMatrix">
    <xsl:param name="matrix" />
    <xsl:param name="dataIndex" />
    <xsl:param name="dimension" />
    <xsl:param name="rowLength" />
    <xsl:param name="row" />
    <xsl:param name="band" />
    
    <xsl:variable name="indent" select="$dimension - $rowLength" />
    <xsl:variable name="perLineGuess" select="$band + 1" />
    
    <xsl:variable name="perLine">
      <xsl:choose>
	<xsl:when test="$perLineGuess + $indent &gt; $dimension">
	  <xsl:value-of select="$dimension - $indent" />
	</xsl:when>
	<xsl:otherwise>
	  <xsl:value-of select="$perLineGuess" />
	</xsl:otherwise>
      </xsl:choose>
    </xsl:variable>
    
    <tr>
      <xsl:call-template name="createEmptyCells">
	<xsl:with-param name="count" select="$indent" />
      </xsl:call-template>
      
      <xsl:call-template name="printCovariationMatrixLine">
	<xsl:with-param name="matrix" select="$matrix" />
	<xsl:with-param name="dataIndex" select="$dataIndex" />
<!--	<xsl:with-param name="dimension" select="$dimension" /> -->
	<xsl:with-param name="rowLength" select="$band + 1" />
	<xsl:with-param name="remaining" select="$perLine" />
      </xsl:call-template>
      
      <xsl:call-template name="createEmptyCells">
	<xsl:with-param name="count" select="$dimension - $indent - $perLine" />
      </xsl:call-template>
    </tr>
    
    <xsl:if test="$row &lt; $dimension">
      <xsl:call-template name="printCovariationMatrix">
	<xsl:with-param name="matrix" select="$matrix" />
	<xsl:with-param name="dataIndex" select="$dataIndex + $perLine" />
	<xsl:with-param name="dimension" select="$dimension" />
	<xsl:with-param name="rowLength" select="$rowLength - 1" />
	<xsl:with-param name="band" select="$band" />
	<xsl:with-param name="row" select="$row + 1" />
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

  
  <!-- Template for printing variance-covariance matrix line -->
  <xsl:template name="printCovariationMatrixLine">
    <xsl:param name="matrix" />
    <xsl:param name="dataIndex" />
<!--    <xsl:param name="dimension" /> -->
    <xsl:param name="rowLength" />
    <xsl:param name="remaining" />
    
    <xsl:variable name="value" select="$matrix/flt[$dataIndex]" />
    
    <td>
      <!--<xsl:value-of select="format-number(round(100*$value) div 100, '0.00')" />-->
      <xsl:value-of select="round(100*$value) div 100" />
    </td>
    
    <xsl:if test="$remaining &gt; 1">
      <xsl:call-template name="printCovariationMatrixLine">
	<xsl:with-param name="matrix" select="$matrix" />
	<xsl:with-param name="dataIndex" select="$dataIndex + 1" />
<!--	<xsl:with-param name="dimension" select="dim" /> -->
	<xsl:with-param name="rowLength" select="$rowLength" />
	<xsl:with-param name="remaining" select="$remaining - 1" />
      </xsl:call-template>
    </xsl:if>
  </xsl:template>

  
  <!-- Template for creating the empty cells while outputing variance-covariance matrix -->
  <xsl:template name="createEmptyCells">
    <xsl:param name="count" select="0" />
    <xsl:if test="$count &gt; 0">
      <td></td>
      <xsl:call-template name="createEmptyCells">
	<xsl:with-param name="count" select="$count - 1" />
      </xsl:call-template>
    </xsl:if>
  </xsl:template>
  

  <!-- Template for converting '\n' to <br/> tag. -->
  <xsl:template name="nl2br">
    <xsl:param name="where" />

    <xsl:variable name="NL">
      <xsl:text>
</xsl:text>
    </xsl:variable>

    <xsl:choose>
      <xsl:when test="string-length($where)=0"></xsl:when>
      <xsl:when test="$where=$NL"><br /></xsl:when>
      <xsl:when test="(substring-after($where, $NL)='') and (substring-before($where, $NL)='')">
	<xsl:value-of select="$where" /></xsl:when>
      <xsl:otherwise>
	<xsl:value-of select="substring-before($where, $NL)" /><br /><xsl:call-template name="nl2br">
	  <xsl:with-param name="where" select="substring-after($where, $NL)" />
      </xsl:call-template></xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  
  <!-- Section "Observations" -->
  <xsl:template match="observations">
    <h4 onclick="changeDisplay('observations')">5. Observations</h4>
    <div id="observations" style="display:none">
      <table border="1">
	<thead>
	  <tr>
	    <th>Type of observation</th>
	    <th>Standpoint</th>
	    <th>Target</th>
	    <th>Observed value [m|g]</th>
	    <th>Adjusted value [m|g]</th>
	    <th>Standard deviation [mm|cc]</th>
	    <th>Q_RR</th>
	    <th>f [%]</th>
	    <th>Error observed [mm|cc]</th>
	    <th>Error adjusted [mm|cc]</th>
	    <th>Standard residual |v'|</th>
	  </tr>
	</thead>
	<xsl:for-each select="//observations/*">
	  <xsl:variable name="observation" select="." />
	  <tr>
	    <td>
	      <xsl:value-of select="name()" />
	    </td>
	    <xsl:for-each select="$observation/*">
	      <td>
		<xsl:value-of select="." />
	      </td>
	    </xsl:for-each>
	  </tr>
	</xsl:for-each>
      </table>
    </div>
    </xsl:template>
    
    
</xsl:stylesheet>
