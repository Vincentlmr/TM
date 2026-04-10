#include "../includes/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGUEUR 100
#define PROGRESS_BAR_WIDTH 50

void display_progress(long current, long total) {
  int progress = (int)((double)current / total * PROGRESS_BAR_WIDTH);
  printf("\rProgress: [");
  for (int i = 0; i < PROGRESS_BAR_WIDTH; ++i) {
    printf(i < progress ? "=" : " ");
  }
  printf("] %.2f%%", (double)current / total * 100);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <fichier_entree> <fichier_sortie>\n", argv[0]);
    return 1;
  }

  char *fichier_entree = argv[1];
  char *fichier_sortie = argv[2];

  FILE *fic = fopen(fichier_entree, "r");
  if (fic == NULL) {
    printf("Erreur: Impossible d'ouvrir le fichier %s\n", fichier_entree);
    return EXIT_FAILURE;
  }

  fseek(fic, 0, SEEK_END);
  long file_size = ftell(fic);
  fseek(fic, 0, SEEK_SET);

  struct liste T;
  init_liste_char(&T);
  char mot[MAX_LONGUEUR];

  long bytes_read = 0;
  printf("Lecture du fichier\n");
  while (fscanf(fic, "%s", mot) != EOF) {
    if (mot[0] != '\0') {
      ajout_liste(&T, mot);
    }
    bytes_read = ftell(fic);
    display_progress(bytes_read, file_size);
  }

  fclose(fic);

  char *tab[T.nbmots];
  int freq[T.nbmots];

  tri_occ(&T, tab, freq);

  fic = fopen(fichier_sortie, "w");
  if (fic == NULL) {
    printf("Erreur: Impossible d'ouvrir le fichier de sortie %s\n",
           fichier_sortie);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < T.nbmots; i++) {
    fprintf(fic, "%s: %d \n", tab[i], freq[i]);
  }
  printf("\n");

  fclose(fic);

  printf("Ecriture dans le fichier de sortie terminée.\n");

  clear_liste(&T, tab);

  return 0;
}
