#include "game.h"
#include "bgame.h"
#include "encryption.h"

#define SUCCESS 0
#define ERROR   1

int test (void);
int TEST_newDisplay();
int TEST_closeDisplay();
int TEST_initGrid();
int TEST_updatePlayerfacing();
int TEST_fillGrid();
int TEST_input();

int TEST_getNeighbour();
int TEST_directionsTrans();
int TEST_newBulb();
int TEST_makeBoundariesBinary();
int TEST_updateEntities();
int TEST_enc_updateWord();
int TEST_enc_getHint();
