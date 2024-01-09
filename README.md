========= PROJET DE STAGE =========

*** DESCRIPTION
	Ce dossier comprend les éléments nécessaires à la bonne mise sur pied du projet. On y retrouve notamment le code du dispositif, le modèle et le serveur. Notre application web est déployée grâce à Anvil [1], elle est accessible via ce lien [2] mais n'affiche de résultats que si le serveur tourne.

*** CONSTITUTION
- codeNPK : code Arduino du dispotif flashé dans un ESP8266
- crop_model.pkl : modèle exporté grâce à Pickle, il permet de faire la prédiction de la culture grâce aux paramètres N, P, K, pH, H (humidité) et T (température)
- serveur_npk.ipynb : Notebook Jupyter qui fait office de code serveur de l'application web. Il se fait grâce à l'option uplink d'Anvil (Server Uplink) qui permet de lancer le serveur en local [3]
- MontageNPK.jpg : schéma du montage

[1] Anvil. Build Web Apps with Nothing Python, [En ligne]. https://anvil.works/
[2] Anvil. NPK mètre, [En ligne]. https://npk-meter.anvil.app/
[3] Anvil Docs. Uplink: Code outside Anvil, [En ligne]. https://anvil.works/docs/uplink