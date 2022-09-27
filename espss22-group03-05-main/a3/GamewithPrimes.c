//------------------------------------------------------------------------------
// a3.c
//
// A programm for the game "Positiv gewinnt"
//
//
// Group: 3
//
//------------------------------------------------------------------------------
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GREEN "\033[0;32m%d\033[0m"
#define BLUE "\033[0;34m%d\033[0m"

typedef struct
{
  int width_of_gamefield;
  int height_of_gamefield;
  char playerOne;
  char playerTwo;
  int tokens;
  char **field;
} Player;

//-----------------------------------------------------------------------------
///
/// This function saves the spaces for my gamefield
///
///
/// @param  struct uses the struct player for my params
///
/// @return the values for the space
//
char gamefield(Player *two)
{
  two->field = malloc(sizeof(char *) * two->height_of_gamefield);
  if (two->field == NULL)
  {
    printf("Out of memory!\n");
    return 4;
  }
  for (int i = 0; i < two->height_of_gamefield; i++)
  {
    two->field[i] = malloc(sizeof(char) * two->width_of_gamefield);
    if (two->field[i] == NULL)
    {
      printf("Out of memory!\n");
      return 4;
    }
    for (int j = 0; j < two->width_of_gamefield; j++)
      two->field[i][j] = ' ';
  }
  return 0;
}
//-----------------------------------------------------------------------------
///
/// This frees my saved memory
///
///
/// @param  ptr* to free my saved space
///
//
void freeGamefield(Player *ptr)
{
  for (int i = 0; i < ptr->height_of_gamefield; ++i)
  {
    free(ptr->field[i]);
  }
  free(ptr->field);
}
//-----------------------------------------------------------------------------
///
/// The char pointer shifts the numbers for my gamefield
///
///
/// @param row  the rows of my game
/// @param size the size of my gamefield
/// @param rotate to put the nunbers as it fits
///
/// @return int age of spouse
//
void rotate(char *row, int size, int rotate)
{
  if (rotate == 0)
  {
    return;
  }
  rotate = size % rotate;
  if (rotate < 0)
  {
    rotate = size - rotate;
  }
  char tmp;
  for (int i = 0; i < size - rotate; i++)
  {
    tmp = row[i];
    row[i] = row[i + rotate];
    row[i + rotate] = tmp;
  }
}
//-----------------------------------------------------------------------------
///
/// This function resizes my game field so i can add and deduct rows and spaces
/// it also checks for invalid commands and frees my new allocated saves
///
/// @param struct all my pramas from struct
/// @param height for the new height
/// @param width  for the new width
///
/// @return 0
//
int resize(Player *game, int height, int width)
{
  int newHeight = game->height_of_gamefield + height;
  int newWidht = game->width_of_gamefield + width;
  if ((height < 0 && width > 0) || (width < 0 && height > 0))
  {
    printf("Invalid Command");
    return 1;
  }
  if (height < 0)
  {
    //make smaller
    for (int i = 0; i < -height; ++i)
    {
      for (int j = 0; j < game->width_of_gamefield; ++j)
      {
        if (game->field[game->height_of_gamefield - 1 - i][j] != ' ')
        {
          printf("Invalid Command\n");
          return 0;
        }
      }
    }
  }
  if (width < 0)
  {
    //make smaller
    for (int i = 0; i < game->height_of_gamefield; ++i)
    {
      for (int j = 0; j < -width / 2; ++j)
      {
        if (game->field[i][j] != ' ')
        {
          printf("Invalid Command\n");
        }
        if (game->field[i][game->width_of_gamefield - 1 - j] != ' ')
        {
          printf("Invalid Command\n");
          return 0;
        }
      }
    }
  }
  if (width % 2 != 0)
  {
    printf("Invalid Command\n");
    return 0;
  }
  char **newgame = malloc(sizeof(char *) * newHeight);
  if (newgame == NULL)
  {
    printf("Out of memory!\n");
    return 4;
  }
  for (int i = 0; i < newHeight; i++)
  {
    newgame[i] = malloc(sizeof(char) * newWidht);
    if (newgame[i] == NULL)
    {
      printf("Out of memory!\n");
      return 4;
    }
    for (int j = 0; j < newWidht; j++)
    {
      char oldchar = ' ';
      if (game->height_of_gamefield > i && game->width_of_gamefield > (j - (width / 2)))
      {
        if (j - (width / 2) >= 0)
        {
          oldchar = game->field[i][j - (width / 2)];
        }
      }
      newgame[i][j] = oldchar;
    }
  }
  freeGamefield(game);
  game->height_of_gamefield = newHeight;
  game->width_of_gamefield = newWidht;
  game->field = newgame;
  return 0;
}
//-----------------------------------------------------------------------------
///
/// This is the function to print my gamefield
/// it also gives my numbers color and every 10th green and every 100th number blue
///
/// @param struct all my params from struct
///
/// @return gamefield
//
void printgamefield(Player *two)
{
  printf("\n");
  for (int a = two->height_of_gamefield - 1; a >= 0; a--)
  {
    printf("|");
    for (int b = 0; b < two->width_of_gamefield; b++)
    {
      if (two->field[a][b] == two->playerOne)
      {
        printf("%s", "\033[0;31mO\033[0m");
      }
      else if (two->field[a][b] == two->playerTwo)
      {
        printf("%s", "\033[0;33mO\033[0m");
      }
      else
      {
        printf(" ");
      }
    }
    printf("|\n");
  }
  printf("-");
  for (int b = 1; b <= two->width_of_gamefield; b++)
  {
    if (b % 10 == 0)
    {
      if (b % 100 == 0)
      {
        printf(BLUE, b / 100);
      }
      else
      {
        printf(GREEN, b / 10);
      }
    }
    else
    {
      printf("%d", b % 10);
    }
  }
  printf("-\n");
}
//-----------------------------------------------------------------------------
///
/// Checks if the first field is empty and starts with one and checks with the first element of the array
/// it checks if the chars in de slots are the same
///
/// @param testfield  a const char pounter to check my fields
/// @param struct all my params from struct
///
/// @return 2
//
int testCharsifSame(const char *testFields, Player *two) // nochmal durchschauen
{

  if (testFields[0] == ' ')
  {
    return 0;
  }
  for (int i = 1; i < two->tokens; ++i)
  {
    if (testFields[i] != testFields[0])
      return 0;
  }
  if (two->playerOne == testFields[0])
  {
    return 1;
  }
  else
  {
    return 2;
  }
}
//-----------------------------------------------------------------------------
///
/// This function checks in every way the winning conditions
///
/// @param struct all my struct params
///
/// @return win
//
int checkWinning(Player *two)
{
  //checkhorizontal
  for (int i = 0; i < two->height_of_gamefield - two->tokens; i++)
  {
    for (int j = 0; j < two->width_of_gamefield; j++)
    {
      char testFields[two->tokens];
      for (int k = 0; k < two->tokens; ++k)
      {
        testFields[k] = two->field[i + k][j];
      }
      int result = testCharsifSame(testFields, two);
      if (result != 0)
        return result;
    }
  }
  //checkvertical
  for (int i = 0; i < two->height_of_gamefield; i++)
  {
    for (int j = 0; j < two->width_of_gamefield - two->tokens; j++)
    {
      char testFields[two->tokens];
      for (int k = 0; k < two->tokens; ++k)
      {
        testFields[k] = two->field[i][j + k];
      }
      int result = testCharsifSame(testFields, two);
      if (result != 0)
        return result;
    }
  }
  //checkdiagonal1
  for (int i = 0; i < two->height_of_gamefield - two->tokens; i++)
  {
    for (int j = 0; j < two->width_of_gamefield - two->tokens; j++)
    {
      char testFields[two->tokens];
      for (int k = 0; k < two->tokens; ++k)
      {
        testFields[k] = two->field[i + k][j + k];
      }
      int result = testCharsifSame(testFields, two);
      if (result != 0)
        return result;
    }
  }
  //checkdiagonal2
  for (int i = 0; i < two->height_of_gamefield - two->tokens; i++)
  {
    for (int j = two->tokens - 1; j < two->width_of_gamefield; j++)
    {
      char testFields[two->tokens];
      for (int k = 0; k < two->tokens; ++k)
      {
        testFields[k] = two->field[i + k][j - k];
      }
      int result = testCharsifSame(testFields, two);
      if (result != 0)
        return result;
    }
  }
  return 0;
}
//-----------------------------------------------------------------------------
///
/// thei functions detects where a token scan go into or so
///
/// @param player the player int to check
/// @param column  The column where the token should go to
/// @param struct  All my params from structs
///
/// @return 1
//
int inputInColumn(int player, Player *two, int column)
{
  if (column - 1 < 0 || column - 1 > two->width_of_gamefield)
  {
    printf("Invalid Command\n");
    return 1;
  }
  if (two->field[two->height_of_gamefield - 1][column - 1] != ' ')
  {
    printf("Invalid Command\n");
    return 1;
  }
  //insert now
  for (int i = 0; i < two->height_of_gamefield; ++i)
  {

    if (two->field[i][column - 1] == ' ')
    {
      char token;
      if (player == 0)
      {
        token = two->playerOne;
      }
      else
      {
        token = two->playerTwo;
      }
      two->field[i][column - 1] = token;
      return 0;
    }
  }
  printf("konnte nicht hinzugefuegt werden\n");
  return 1;
}
//-----------------------------------------------------------------------------
///
/// This function chechs for the comands that can be used in the Game
/// it also prints the players in color and checks for invalid commands
///
/// @param player the int to check for the right player
/// @param struct All my params from the struct
///
/// @return ß
//
int enterCommand(int player, Player *two)
{
  //enter input

  while (1)
  {
    char input[256];
    if (player)
    {
      printf("\033[0;33mPlayer 2\033[0m > ");
    }
    else
    {
      printf("\033[0;31mPlayer 1\033[0m > ");
    }

    scanf("%[^\n]%*c", input);
    if (strspn(input, "0123456789") == strlen(input))
    {
      int number = 0;
      sscanf(input, "%u%*c", &number);
      int result = inputInColumn(player, two, number);
      if (result == 0)
        return 0;
    }
    else if (strcmp(input, "surrender") == 0)
    {
      return 1;
    }
    else if (memcmp(input, "extend", strlen("extend")) == 0)
    {
      char *split = strtok(input, " ");
      char *arg[3];
      int i = 0;
      while (split != NULL)
      {
        if (i > 3)
        {
          printf("Invalid Command\n");
          return 1;
        }
        arg[i++] = split;
        split = strtok(NULL, " ");
      }

      int resizeheight = atoi(arg[2]);
      int resizewidht = atoi(arg[1]);
      resize(two, resizeheight, resizewidht);
      if (resizewidht<0 & resizeheight> 0 || resizeheight<0 & resizewidht> 0)
      {
      }
      else
      {
        printgamefield(two);
      }

      //int result = resize(two, resizeheight, resizewidht);
      return 2;
    }
    else
    {
      printf("Invalid Command\n");
    }
  }
}

//------------------------------------------------------------------------------
///
/// The main program.
/// Reads three numbers for my token , width and height
/// prints a lot of error messages
///
/// @param argv  for my tokens
/// @param argv for my height
/// @param argv for my width
///
/// @return always zero
//
int main(int argc, char *argv[])
{
  Player two;
  if (argc != 4)
  {
    printf("Wrong amount of parameters!\n");
    return 1;
  }
  two.tokens = atoi(argv[1]);
  two.width_of_gamefield = atoi(argv[2]);
  two.height_of_gamefield = atoi(argv[3]);
  two.playerOne = 'x';
  two.playerTwo = '0';

  if (two.tokens < 1 || two.width_of_gamefield < 1 || two.height_of_gamefield < 1)
  {
    printf("Invalid arguments!\n");
    return 2;
  }
  gamefield(&two);
  printgamefield(&two);
  int currentplayer = 0;

  while (1)
  {
    printf("\n");
    int surrender = enterCommand(currentplayer, &two);
    if (surrender == 1)
    {
      if (currentplayer == 1)
      {
        printf("\033[0;31mPlayer 1\033[0m won!\n");
      }
      else
      {
        printf("\033[0;33mPlayer 2\033[0m won!\n");
      }
      break;
    }
    if (surrender == 2)
    {
      continue;
    }
    printgamefield(&two);

    int result = checkWinning(&two);
    currentplayer = !currentplayer;
    if (result == 0)
    {
      continue;
    }
    printf("\n");
    if (result == 1)
    {
      printf("\033[0;31mPlayer 1\033[0m won!\n");
    }
    else
    {
      printf("\033[0;33mPlayer 2\033[0m won!\n");
    }
    break;
  }
  freeGamefield(&two);
  return 0;
}
