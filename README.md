# projet
Q1 : Quelles sont les structures de données à utiliser ?
Rep1:
Structures de données :
On utilise des tableaux bidimensionnels pour les matrices B, C et A
Pour le tampon T, on utilise un tableau ou une file(queue) dont la taille correspond aux résultats intermédiaires attendus.

Q2 : Comment allez-vous protéger l'accès à ces données ?
Rep2:
Protection de l'accès aux données :
On utilise des verrous (mutex) pour contrôler l'accès concurrentiel aux données partagées, tels que les matrices et le tampon. Acquérez le verrou avant d'accéder aux données et libérez-le après utilisation.
On utilise des sémaphores pour gérer l'accès au tampon. Les sémaphores régulent le nombre de places libres dans le tampon et le nombre d'éléments produits ou consommés.
Q3 : Quels sont les risques ?
Rep3:
1.Conditions de course (Race conditions):Les threads producteurs pourraient essayer d'écrire dans le tampon T simultanément, entraînant des résultats imprévisibles.
2.Deadlocks : Si la synchronisation entre les threads n'est pas gérée correctement, des situations de blocage mutuel (deadlocks) peuvent survenir, où les threads se bloquent en attendant que d'autres ressources soient libérées.
3.Problèmes de performances : Une mauvaise gestion de la synchronisation peut entraîner des problèmes de performances en raison de l'attente excessive des threads pour accéder aux données partagées




