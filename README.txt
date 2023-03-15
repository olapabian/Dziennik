Program prezentuje uproszczony dziennik szkolny. Zawiera dwie klasy reprezentujące uczniów i grupy.
Program wczytuje plik uczniowie.txt. Każdy wiersz tego pliku zawiera informacje o jednym uczniu w następującej formie:

numer_grupy ocena_z_zachowania ilość_ocen ocena_1 ocena_2 ... ocena_n     ---     gdzie n jest ilością ocen

Dla każdego wiersza z pliku:
-tworzy ucznia w odpowiedniej grupie 
-przyznaje nagrody uczniom (przyznanie nagrody oznacza zwiększenie licznika zdobytych nagród danemu uczniowi)
	-O najwyższej średniej ocen w danej grupie (jeśli jest więcej niż jeden uczeń w danej grupie o najwyższej średniej, przydziel nagrodę im wszystkim)
	-O najwyższej średniej ze wszystkich uczniów (ponownie, w przypadku remisu przydziel nagrodę wszystkim uczniom)
	-Wszystkim uczniom, którzy mają przynajmniej pięć ocen >=5
	-Wszystkim uczniom o ocenie z zachowania == 6
Wypisuje ilu uczniów dostało nie dostało żadnej nagrody, ilu jedną, ilu dwie itd
