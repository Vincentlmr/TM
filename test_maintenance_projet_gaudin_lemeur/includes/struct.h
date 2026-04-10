struct maillon {
  char mot[100];
  int freq;
  struct maillon *suivant;
};

struct liste {
  struct maillon *tete;
  int nbmots;
};

#define NIL (struct maillon *)0

extern void init_liste_char(struct liste *);
extern void ajout_liste(struct liste *, char[100]);
extern void tri_occ(struct liste *, char **, int *);
extern void clear_liste(struct liste *, char **);
