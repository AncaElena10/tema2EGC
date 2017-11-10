Tema2 EGC - Build and Survive
Moisa Anca-Elena
331CA

Mult cod duplicat. Se apropia deadline-ul.

Utilizare aplicatie
-------------------

Eroul se misca cu tastele W(in fata), A(la stanga), S(in spate), D(la dreapta), cat timp se tine apasat 
click dreapta. In ace;asi timp, se va misca si camera impreuna cu eroul
Inamicii au 4 vieti.
1 - va activa un pistol; gloantele se misca cu o viteza mica, pe o distanta scurta, insa sunt puternice, 
ele eliminand 2 vieti ale unui inamic
2 - se activeaza camera firstPerson, si totodata o pusca; aceasta este rapida, se duce pe o distanta mare, 
insa nu este la fel de puternica; vor fi necesare 8 gloante pentru a distruge un inamic
3 - se activeaza grenada; aceasta este foarte puternica, se lanseaza cu bolta pe o distanta relativ mica, 
insa distruge toate cele 4 vieti ale inamicului
Armele pot fi folosite cu click-stanga
Camera se invarte cu ajutorul mouse-ului (click dreapta); in timp ce camera se invarte, eroul va ramane 
mereu cu spatele la cel care se joaca

Detalii de implementare
-----------------------

Folosesc: un fisier LabCamera.h care realizeaza rotatiile first si third person
		  un fisier Transform3D.h care realizeaza functiile de translatie, rotatie(pe OX, OY, OZ) si scalare
		  un fisier Laborator5.h in care imi creez pentru fiecare obiect in parte cate o structura in care retin 
		  anumite date despre obiecte, cum ar fi pozitiile initiale, unghiul cu care se rotesc, viteza cu 
		  care se deplaseaza etc
		  un fisier Laborator5.cpp in care efectuez implementarea efectiva

Laborator5.cpp

Initial creez cate un mesh pentru fiecare obiect
In functia Update randez pe rand, elementele
RenderHero() - imi randeaza eroul; il rotesc initial cu 180 de grade astfel incat sa stea cu spatele la inceput, apoi
			   il rotesc cu unghiul camerei, astfel incat sa ramana mereu cu spatele, si in centrul scenei
RenderEnemy() + GenerateEnemy() - la fiecare 5 secunde generez cate un inamic; el porneste din pozitia (-8, 0, -8) 
								  si se deplaseaza catre pozitia (8, 0, 8) in forma de Z
								- cand inamicul ajunge la diagonala, il rotesc cu 225 de grade, pentru a-si pastra 
								  pozitia catre directia spre care se deplaseaza
								- cand inamicul ajunge la (8, 0, 8), el il sterg din vector
								- pentru fiecare inamic ajuns la capatul, eu pierd o viata
Generare grenada, pusca, pistol - la fiecare click stanga, in functie de tasta apasata (1, 2, 3), se va genera un 
								  obiect de tipul grenada, pistol sau pusca (la generare, ii stabilesc pozitiile de 
								  pornire si unghiul - unghiul este cel de rotire al eroului)
Coliziuni - coliziunile se bazeaza pe sfere
		  - cand o grenada, pusca, sau pistolul intalnesc un inamic -> toate elementele vor fi sterse din vector
		  - inainte de a fi stersi, inamicii realizeaza o animatie de cadere in lateral, apoi dispar

Mentiuni
--------

Inamicii parcurg un labirint in forma de Z hardcodat
Eroul are in jurul lui 3 bile - acestea se rotesc in jurul axelor OX, OY, OZ - ele reprezinta vietile; in momentul in
in care un inamic atinge punctul (8, 0, 8) - eroul pierde o viata; cand eroul nu mai are vieti, jocul se incheie
Cand jocul se incheie, eroul cade in lateral si armele si deplasarea ii sunt dezactivate
Exista 3 turnuri ajutatoare care se vor invarti dupa inamici si ii vor impusca; ei vor lua cate o viata din cele 4 ale 
unui inamic.

Am lucrat doar in fisierele aflate in Source->Laboratoare->Laborator5
