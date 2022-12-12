from random import randint
import numpy as np

sum = 0

print("Expérience")

for i in range(50):
    compteur = 0
    bon = 0
    test = np.zeros((1, 576))
    while bon < 576:
        r = randint(0, 575)
        if test[0][r] == 0:
            test[0][r] = 1
            bon += 1
        compteur += 1
    sum += compteur
    print(" Essai", i+1, ":", compteur)

print("\nMoyenne d'essais : ", int(sum/50))