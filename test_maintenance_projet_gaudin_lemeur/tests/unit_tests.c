/**
 * @brief      This file implements unit tests for sorting algorithms
 *
 */
#include <check.h>
#include <stdlib.h>
#include <struct.h>

#define MAX_LONGUEUR 100
/**
 * @brief Simple test that checks whether the random number generator has
 *        has been initialized
 */

// vérifie qu'une liste est bien initialisée avec un nombre de mot de 0.
START_TEST(test_init) {
  struct liste T;
  init_liste_char(&T);
  ck_assert_int_eq(T.nbmots, 0);
}
END_TEST

// vérifie que l'ajout d'un mot dans une liste focntionne.
START_TEST(test_array) {
  struct liste T;
  char mot[MAX_LONGUEUR] = "Bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, mot);
  ck_assert_int_eq(T.nbmots, 1);
}
END_TEST

// vérifie que le même mot ne s'ajoute pas 2 fois dans la liste.
START_TEST(test_2mots_egaux) {
  struct liste T;
  char mot[MAX_LONGUEUR] = "Bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, mot);
  ajout_liste(&T, mot);
  ck_assert_int_eq(T.nbmots, 1);
}
END_TEST

// vérifie que que si l'on ajoute un mot avec de la ponctuation collé au début
// ou à la fin la liste reconnait le mot sans la //ponctuation.
START_TEST(test_ponctuation) {
  struct liste T;
  char mot[MAX_LONGUEUR] = "bonjour.\0";
  char motverif[MAX_LONGUEUR] = "bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, mot);
  ck_assert_str_eq(T.tete->mot, motverif);
}
END_TEST

// vérifie que la fonction de tri par fréquence fonctionne correctement.
START_TEST(test_tri_freq) {
  struct liste T;
  char motdiff[MAX_LONGUEUR] = "hello\0";
  char mot[MAX_LONGUEUR] = "bonjour\0";
  char mot2[MAX_LONGUEUR] = "bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, motdiff);
  ajout_liste(&T, mot);
  ajout_liste(&T, mot2);
  char *tab[T.nbmots];
  int freq[T.nbmots];
  tri_occ(&T, tab, freq);
  ck_assert_int_eq(freq[0], 2);
}
END_TEST

// vérifie que la fonctionn de tri des mots fonctionne correctement.
START_TEST(test_tri_mot) {
  struct liste T;
  char motdiff[MAX_LONGUEUR] = "hello\0";
  char mot[MAX_LONGUEUR] = "bonjour\0";
  char mot2[MAX_LONGUEUR] = "bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, motdiff);
  ajout_liste(&T, mot);
  ajout_liste(&T, mot2);
  char *tab[T.nbmots];
  int freq[T.nbmots];
  tri_occ(&T, tab, freq);
  ck_assert_str_eq(tab[0], mot);
}
END_TEST

// vérifie que si l'on ajoute un mot avec une majuscule , la liste reconnait le
// mot sans la majuscule.
START_TEST(test_majuscule) {
  struct liste T;
  char mot[100] = "Bonjour.\0";
  char mot2[100] = "bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, mot);
  ajout_liste(&T, mot2);
  ck_assert_int_eq(T.nbmots, 1);
}
END_TEST

// vérifie que la fonction de tri fonctionne correctement lorsque les fréquance
// de mots sont similaires.
START_TEST(test_tri_ordre_alpha) {
  struct liste T;
  char mot1[MAX_LONGUEUR] = "hello\0";
  char mot2[MAX_LONGUEUR] = "bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, mot1);
  ajout_liste(&T, mot2);
  char *tab[T.nbmots];
  int freq[T.nbmots];
  tri_occ(&T, tab, freq);
  ck_assert_str_eq(tab[0], mot2);
}
END_TEST

// vérifie que le nombre de mot d'une liste revienne à 0 après avoir utilisé
// clear_liste, et vérifie que le tableau des mots ordonnés après tri_occ coit
// vide.
START_TEST(test_clear_liste) {
  struct liste T;
  char mot1[MAX_LONGUEUR] = "hello\0";
  char mot2[MAX_LONGUEUR] = "bonjour\0";
  init_liste_char(&T);
  ajout_liste(&T, mot1);
  ajout_liste(&T, mot2);
  char *tab[T.nbmots];
  int freq[T.nbmots];
  tri_occ(&T, tab, freq);
  clear_liste(&T, tab);
  ck_assert_int_eq(T.nbmots, 0);
  for (int i = 0; i < T.nbmots; i++) {
    ck_assert_ptr_eq(tab[i], NULL);
  }
}
END_TEST

END_TEST Suite *sort_suite(void) {
  Suite *s = suite_create("SortText");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_init);
  tcase_add_test(tc_core, test_array);
  tcase_add_test(tc_core, test_2mots_egaux);
  tcase_add_test(tc_core, test_ponctuation);
  tcase_add_test(tc_core, test_majuscule);
  tcase_add_test(tc_core, test_tri_freq);
  tcase_add_test(tc_core, test_tri_mot);
  tcase_add_test(tc_core, test_tri_ordre_alpha);
  tcase_add_test(tc_core, test_clear_liste);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;
  Suite *s = sort_suite();
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
