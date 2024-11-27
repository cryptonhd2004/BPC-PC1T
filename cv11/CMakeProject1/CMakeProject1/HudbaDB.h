#ifndef HUDDBA_DB_H
#define HUDDBA_DB_H

#define INTERPRET_SIZE 100
#define NAZEV_ALBA_SIZE 100

struct t_HudbaDB {
    char interpret[INTERPRET_SIZE];    
    char nazev_alba[NAZEV_ALBA_SIZE];  
    int rok_vydani;                    
    struct t_HudbaDB* dalsi;           
};

void add(const char* interpret, const char* nazev_alba, int rok_vydani, struct t_HudbaDB** uk_prvni);

void del(int rok_vydani, struct t_HudbaDB** uk_prvni);

void vypisSeznam(struct t_HudbaDB* uk_prvni);

void vypisSeznamPodlePismena(struct t_HudbaDB* uk_prvni);

#endif 
