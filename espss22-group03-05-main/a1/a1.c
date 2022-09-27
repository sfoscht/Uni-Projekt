//------------------------------------------------------------------------------
// a1.c
//
// A programm for prime approximation
//
//
// Group: 3
//
// Author: 12044152
//------------------------------------------------------------------------------
//
#include <stdio.h>

//------------------------------------------------------------------------------
///
/// a function to clean the input buffer.
///
///
/// @return void
//
void clear(void)
{
  while (getchar() != '\n');
}

//------------------------------------------------------------------------------
///
/// reads STDIN until a valide integer Input has been given
///
/// @param message instruction for the user
///
/// @return validated integer user input
//
int readInput(char *message)
{
  int input = 0;
  while (1)
  {
    printf("%s", message); //%S = Platzhalter für variable
    /*
    scanf  gibt will mit %i (platzhalter) eine ganze zahl anzeigen und &input soll überschrieben werden.
    falls dies nicht der fall ist  und nicht überschrieben wird (=0) wird danach fehler behoben dh.kein interger eingegeben.
    wenn integer eingegeben ( = 1) 
    */
    if (scanf("%i", &input) == 0)
    {
      clear();
      continue; // geh zum Anfang der schleife zurück
    }
    if (input >= 2 && input <= 2022)
    {
      return input;
    }
  }
} // butler = funktion

//------------------------------------------------------------------------------
///
/// reads STDIN until a valid double Input has been given
///
///
/// @return validated double user input
//
double sizeOfThreshold()
{
  double input = 0;
  while (1)
  {
    printf("size of threshold: ");
    if (scanf("%lf", &input) == 0)
    {
      clear();
      continue;
    }
    if (input >= 0.0002 && input <= 0.2)
    {
      return input;
    }
  }
}

//------------------------------------------------------------------------------
///
/// Calculates Zeta based on a Primenumber
///
/// @param number primesnumber used for the calculation
///
/// @return calculated result for Zeta
//
double calculateZeta(int number)
{
  return (1 / (1 - (1 / ((double)number * (double)number))));
}

//------------------------------------------------------------------------------
///
/// Calculates Primenumbers,reference Zeta,Zeta and it aproximates the primenumbers also prints results of the calculations.
///
/// @param limit  limit of sieve
/// @param calculated_reference_zeta the result of the zeta caluclation
/// @param threshold threshold for the calculation
///
/// @return void
//
void printAndCalculateResults(const int limit, double calculated_reference_zeta, double threshold)
{
  int count = 0;
  int index_counter = 0;
  int primes[limit];

  for (int current = 1; current <= limit; current++)
  {
    count = 0;

    for (int index = 2; index <= current / 2; index++)
    {
      if (current % index == 0)
      {
        count++;
      }
    }
    // nach jeder 10ten primzahl ne neue reihe
    if ((current - 1) % 10 == 0)
      printf("\n");

    if (current == 1)
      printf("	");
    else if (count == 0) // count 0 = keine primzahl
    {
      printf("%d	", current);
      primes[index_counter++] = current;
    }
    else
      printf("0	");
  }

  printf("\n-------------------------------------------------------------------------\n");
  printf("available primes: ");

  for (int i = 0; i < index_counter; i++)
  {
    printf("%i ", primes[i]); // in rechnung counten und dann als grenze + primes printen
  }
  printf("\n");
  double zeta = 1;

  for (int a = 0; a < index_counter; a++)
  {
    printf("\nusing primes: ");
    for (int i = 0; i <= a; i++)
    {
      printf("%d ", primes[i]);
    }
    printf("\n");

    zeta *= calculateZeta(primes[a]); // multipliziert mit Zeta

    printf("current zeta: %.5lf\n", zeta);
    if (zeta >= calculated_reference_zeta - threshold)
    {
      printf("\nApproximation found!\nYou need the first %d prime numbers to reach %.5lf with a threshold of %.5lf.\n", a + 1, calculated_reference_zeta, threshold);
      return;
    }
  }

  printf("\nNo approximation found!\n");
}

//------------------------------------------------------------------------------
///
/// The main program.
/// Reads three numbers from stdin and prints their primenumber aproximation to stdout.
///
///
/// @return always zero
//
int main(void)
{
  const int summand_count = readInput("number of summands: ");
  const int limit_of_sieve = readInput("limit of sieve: ");
  const double threshold = sizeOfThreshold();

  double reference_zeta = 0;
  for (int maxN = 1; maxN <= summand_count; maxN++)
  {
    reference_zeta += (1 / ((double)maxN * maxN));
  }

  printf("\nreference zeta: %.5lf\n", reference_zeta);
  printAndCalculateResults(limit_of_sieve, reference_zeta, threshold);

  return 0;
}
