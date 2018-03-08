
------------------- M1 INFORMATIQUE LILLE1----------------------------

-------------------    M3DS 2017-2018	  ----------------------------


Afrass Ilias


Tout à été fait et fonctionne parfaitement (même la question Bonus 25).


Question 7 :
	Le premier triangle tracé est le triangle rouge,
	le deuxième en vert cache la moitié du premier et ainsi de suite 
	jusqu'au tracé du dernier triangle cyan qui cache la deuxième moitié
	du triangle rouge et la moitié du triangle bleu.
	c'est à dire openGl affiche le dernier pixel tracé sachant qu'il y a pas d'élimination des parties cachées.

Question 8:
	en activant le depth buffer, OpenGL affiche les triangles rouge et bleu 
	parce que ces triangles étant en avant en profendeur par rapport au deux autres.

Question 9:
1/
	en changeant le test du depth buffer en GL_GREATER au lieu de GL_LESS,
	le test passe si depth(src) > depth(dst) 
	et comme la valeur d'initialisation du depth destination de tous les pixels lors d'un glClear est 
	initialisé à 1 (Définir la profondeur de fond la plus éloignée)
	avec l'instruction glClearDepth(1); donc on va jamais reussir le test  d'où 
	OpenGL va rien afficher (écran blanc).

2/
	en changeant le glClearDepth avec la valeur 0 (Définir la profondeur de fond la plus proche)
	c'est à dire que la valeur d'initialisation du depth destination de tous les pixels lors d'un glClear
	est initialisé à 0(),les triangles vert et cyon étant plus grands en profendeur par rapport au deux autres,
	ils vont être afficher.


3/
	Comme les points aux extrémités sont plus petits par rapport à 0.5, ils ne sont pas affichés.


5/Objets plus complexes:
	pour un cube, avec une couleur par face, il faudrait 4*6 = 24 sommets.

 
Question 12/
	on peux modifier le repère pour le rendre plus intuitif
 