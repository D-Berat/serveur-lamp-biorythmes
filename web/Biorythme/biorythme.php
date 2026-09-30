<html>
<head>
	<title>Biorythmes</title>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
    <meta name="language" content="fr" />
	<link rel="stylesheet" type="text/css" href="css/style.css" />
	<link rel="shortcut icon" href="biorythme.ico"/>
</head>
<body>
<?php
	$now = date("d-m-Y");
	echo $now;
?>
<center>
<div class="centreVertical">
    <form id="formulaire" method="get" action="../cgi-bin/biorythme.cgi">
	     Date de naissance (jj mm aaaa) :
	     <input id="jour" type="texte" size="2" maxlength="2" value="" name="jour" />
	     <input id="mois" type="texte" size="2" maxlength="2" value="" name="mois" />
	     <input id="an"   type="texte" size="4" maxlength="4" value="" name="an" /><br />
	     <input class="boutonNormal" type="reset"  value="Effacer" />
	     <input class="boutonNormal" type="submit" value="Valider" />
    </form>
</div>
</center>
</body>
</html>
