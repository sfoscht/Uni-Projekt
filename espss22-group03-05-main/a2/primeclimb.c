
//------------------------------------------------------------------------------
// a2.c
//
// A programm for prime a Prime Climb
//
//
// Group: 3
//
// 
//------------------------------------------------------------------------------
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Max_player 3 // MY MAXplayers for the game

struct _Player_
{
  char symbol;
  int place;
};
struct Game
{
  int dice_1, dice_2;
  struct _Player_ one[Max_player];
  int player_count;
  int field_count;
};
//-----------------------------------------------------------------------------
/// This function defines my player smybol
///
/// @param player_count the number from my field
//
int playersymbol(struct Game *);
int playerSymbol(struct Game *two, int player_count)
{
  for (int i = 0; i < player_count; i++)
  {
    printf("Enter symbol for player %d: ", (i + 1));
    scanf(" %c", &two->one[i].symbol); // auf struct zu greifen
    if (getchar() == EOF)
    {
      exit(0);
    }
    {
      for (int j = 0; j < i; j++)
      {
        if (two->one[i].symbol == two->one[j].symbol)
        {
          printf("Was already chosen by player %d, enter again!\n", (j + 1));
          i--;
        }
      }
    }
  }
  printf("\n");
  return 0;
}
//-----------------------------------------------------------------------------
///
/// This function makes a random dice with 10 surfaces
///
/// @return the randomnes
//
// würfel machen
int diceNumber()
{
  return rand() % 10 + 1;
}
//-----------------------------------------------------------------------------
///
/// This function rolls the dice twice
///
/// @param dice_1 first  random dice
/// @param dice_2  second random dice
///
//
// dice roll 2x
int diceRoll(struct Game *two)
{
  two->dice_1 = diceNumber();
  two->dice_2 = diceNumber();
  printf("\033[1mValue of first dice was %d\033[0m\n", two->dice_1);
  printf("\033[1mValue of second dice was %d\033[0m\n", two->dice_2);
  return 0;
}
//-----------------------------------------------------------------------------
/// This function colors my number
///
/// @param number the number from my field
/// @param color  the color for my number
///@param without_color the number without color
//
void printNumbercolored(int number)
{
  char without_color[] = "\033[0m";
  const char *color;
  if (number == 2)
  {
    color = "\033[0;33m";
  }
  if (number == 3)
  {
    color = "\033[0;32m";
  }
  if (number == 5)
  {
    color = "\033[0;34m";
  }
  if (number == 7)
  {
    color = "\033[0;35m";
  }
  if (number > 7)
  {
    color = "\033[0;31m";
  }
  printf("%s%d%s", color, number, without_color);
}
void reset()
{
  printf("\033[0m");
}
//-----------------------------------------------------------------------------
// from: https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
//  created with the help of tutor Lukas
//B multiplies all factors till i have my field_count thenm print no \n
// A function to print all prime factors of a given number n
void primefactorisation(int field_count)
{
  // Print the number of 2s that divide field_count
  int field = field_count;
  int ka = 1;
  while (field_count % 2 == 0)
  {
    printNumbercolored(2);
    field_count = field_count / 2;
    ka = ka * 2;
    if (ka != field)
      printf(" ");
  }

  // field_count must be odd at this point.  So we can skip
  // one element (Note i = i +2)
  for (int i = 3; i <= sqrt(field_count); i = i + 2)
  {
    // While i divides field_count, print i and divide field_count
    while (field_count % i == 0)
    {
      printNumbercolored(i);
      field_count = field_count / i;
      ka = ka * i;
      if (ka != field)
        printf(" ");
    }
  }

  // This condition is to handle the case when field_count
  // is a prime number greater than 2
  if (field_count > 2)
    printNumbercolored(field_count);
  ka = ka * field_count;
  if (ka != field)
    printf(" ");
}

//End
//-----------------------------------------------------------------------------
///
/// The Function checks if the given number is a prime number
///
/// @param i .
/// @param field_count the number I tipe in
/// @param flag to check that 0 is not used
///
/// @return1
//
int checkPrime(int field_count) // primfaktorzerlegung einbauen
{
  int i, flag = 0;

  // 0 and 1 are not prime numbers
  // change flag to 1 for non-prime number
  if (field_count == 0 || field_count == 1)
    flag = 1;

  for (i = 2; i <= field_count / 2; ++i)
  {

    // if field_count is divisible by i, then field_count is not prime
    // change flag to 1 for non-prime number
    if (field_count % i == 0)
    {
      flag = 1;
      break;
    }
  }
  // flag is 0 for prime numbers
  if (flag == 0)
    return 0;
  else
    return 1;
}
//-----------------------------------------------------------------------------
///
/// The Function prints my field and the position my player is
/// @param field_count The field it is on
/// @param player_count the symbols
///
//
void fieldPrint(struct Game *two, int player_count, int field_count)
{
  printf("-------------------------------------------------\n");
  printf("|Player\t\tField\t\tPrime Factors\t|\n");
  printf("-------------------------------------------------\n");

  for (int i = 0; i <= field_count; i++)
  {
    for (int j = 0; j < player_count; j++)
    {
      if (two->one[j].place == i)
        printf("%c", two->one[j].symbol);
    }
    printf("\t\t%d\t\t", i);
    if (i > 1)
      primefactorisation(i);
    printf("\n");
  }
  //reset();
  printf("-------------------------------------------------\n");
}
//-----------------------------------------------------------------------------
///
/// The Function collects the information  my player moves to
///
/// @param to_field  the field it moves to
/// @param field_count on wich field he starts
///
//
void movePlayer(struct Game *two, int player_number, int toField, int player_count)
{
  two->one[player_number].place = toField;
  for (int i = 0; i < player_count; i++)
  {
    if (two->one[player_number].place == two->one[i].place)
      if (i != player_number && toField != 0)
      {
        printf("Player %c was busted\n", two->one[i].symbol);
        two->one[i].place = 0;
      }
  }
}
//-----------------------------------------------------------------------------
///
/// The Function calculates the place my player moves to
///
/// @param actual_dice The human to check.
/// @param number_to_return_if_not_married The number to return if the human
///        is not married. Should be 0 or 1 for example purposes.
///
/// @return my 2 forms of invalid operation
//
int calculatePlace(struct Game *two, int player_number, int decition_dice, char userInput)
{
  int actual_dice;
  int calculated_field;
  if (decition_dice == 0)
    actual_dice = two->dice_1;
  else
    actual_dice = two->dice_2;
  switch (userInput)
  {
  case '+':
    calculated_field = actual_dice + two->one[player_number].place;
    break;
  case '-':
    calculated_field = two->one[player_number].place - actual_dice;
    break;
  case '/':
    calculated_field = two->one[player_number].place / actual_dice;
    break;
  case '*':
    calculated_field = actual_dice * two->one[player_number].place;
    break;
  case EOF:
    exit(-1);
  default:
    printf("Operation is invalid, try it again:\n");
    return 1;
    break;
  }
  if ((two->field_count - two->one[player_number].place <= 10 && userInput != '+') || calculated_field < 0)
  {
    printf("Operation is invalid, try it again:\n");
    return 1;
  }

  movePlayer(two, player_number, calculated_field, two->player_count);
  return 0;
}
//-----------------------------------------------------------------------------
///
/// This funktion has my win condition and the position of my player
///
/// @param userinput the input of my user
///
//
void playMove(struct Game *two, int player_number)
{
  char user_input;
  diceRoll(two);
  for (int i = 0; i < 2; i++)
  {
    if (i == 1)
      printf("\n\033[1mValue of second dice was %d\033[0m\n", two->dice_2);
    printf("\nChoose between:\nadd: +\nsub: -\nmul: *\ndiv: /\n\n");
    do
    {
      printf("> ");
      while (1)
      {
        scanf(" %c", &user_input);
        char e = getchar();
        if (e == EOF)
        {
          exit(0);
        }
        if (e == '\n')
          break;
      }
    } while (calculatePlace(two, player_number, i, user_input) != 0);
    printf("Player %c moved to Field %d\n\n", two->one[player_number].symbol, two->one[player_number].place);
    fieldPrint(two, two->player_count, two->field_count);
    if (two->one[player_number].place == two->field_count)
    {
      printf("Player %c won the Game\n", two->one[player_number].symbol); //my player
      exit(EXIT_SUCCESS);                                                 // geht aus programm raus
    }
  }
  printf("\n");
}
//------------------------------------------------------------------------------
///
/// The main program.
/// Reads three numbers from stdin and prints only the seed.
/// prints a lot of error messages
///
/// @param argv  for my Seed
/// @param argv for my player count
/// @param argv for my field_count
///
/// @return always zero
//
int main(int argc, char *argv[])
{
  struct Game game;
  if (argc != 4)
  {
    printf("Wrong amount of parameters!\n");
    return 1;
  }
  int seed = atoi(argv[1]);
  game.player_count = atoi(argv[2]);
  game.field_count = atoi(argv[3]);
  if (game.field_count <= 0)
  {
    printf("Gamefield has to consist of at least 1 field (without zero)\n");
    return 4;
  }

  if (game.player_count > 3 || game.player_count < 1)
  {
    printf("Number of Players should be greater than 0, but smaller than 4!\n");
    return 3;
  }
  srand(seed);
  if (checkPrime(game.field_count) != 0)
  {
    printf("Last field has to be prime!\n");
    return 5;
  }
  else
  {
    if (seed <= 1)
    {
      printf("Invalid arguments!\n");
      return 2;
    }
    else
    {
      printf("Chosen seed was: %i\n", seed);
    }

    if (playerSymbol(&game, game.player_count) == -1)
    {
      return 0;
    }
    game.one[0].place = 0;
    game.one[1].place = 0;
    fieldPrint(&game, game.player_count, game.field_count);
    printf("\n");
    while (1)
    {
      for (int i = 0; i < game.player_count; i++)
      {
        printf("Player %c, it is your turn!\n\n", game.one[i].symbol);
        playMove(&game, i);
      }
    }
    return 0;
  }
}
