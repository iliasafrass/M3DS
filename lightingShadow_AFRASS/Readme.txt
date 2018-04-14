
AFRASS ILIAS


Tout à été fait et fonctionne parfaitement.


2/Question3:
  Car le sol n'a pas de vertex et que si on calcule par pixels le sol est éclairé partout.

3/Exercice1/Question1:
  * L'image est fixe car sa projection l'image suit la caméra.
  * Les coordonnées de texture vont de 0 à 1, donc n'aparaissent que dans le quart supérieur droit de l'écran (le repère allant de -1 à 1).
  * On ne voit pas la texture dans le fond de la scène car l'image est projetée sur des surfaces, le fond de la scène n'a pas de surface.

3/Exercice1/Question4:
  Les pixels en coordonnées négatives cherchent donc dans la texture les pixels avec des coordonnées de 0 à 1.

3/Exercice1/Question5:
  * Chaque objet a son propre repère. Donc ils ne partagent pas la même position.
  * L'image est projetée par rapport à partir de la caméra. Ce test est intéressant car il faut projeter l'image à partir du projecteur, donc il faut utiliser le même principe mais avec la position du projecteur.

3/Exercice2/Question6:
depthMap : fragColor.r correspond à la distance entre la source lumineuse et le pixel de l'objet le plus proche de cette source (ce qui explique pourquoi l'avion est plus sombre et la voiture plus claire)

screen : fragColor.r correspond toujours à la profondeur de l'objet le plus proche de la source. texCoord.z correspond à la profondeur du pixel de l'objet que l'on veut dessiner.

On vérifie si fragColor.r < texCoord.z, si c'est le cas, c'est qu'il y a un objet entre la source lumineuse et le pixel, on ne l'éclaire donc pas.