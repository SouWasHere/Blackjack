using System;
using System.Collections.Generic;

class BlackjackGame
{
    static Random random = new Random();

    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        Console.WriteLine("Welcome to Multiplayer Blackjack!");
        Console.Write("Enter number of players (2-4): ");
        int playerCount;

        while (!int.TryParse(Console.ReadLine(), out playerCount) || playerCount < 2 || playerCount > 4)
        {
            Console.Write("Invalid input. Please enter a number between 2 and 4: ");
        }

        PlayBlackjack(playerCount);
    }

    static void PlayBlackjack(int playerCount)
    {
        
        List<List<string>> playerHands = new List<List<string>>();
        List<int> playerTotals = new List<int>();
        for (int i = 0; i < playerCount; i++)
        {
            playerHands.Add(new List<string> { DrawCard(), DrawCard() });
            playerTotals.Add(0);
        }

        List<string> dealerHand = new List<string> { DrawCard(), DrawCard() };

        Console.WriteLine($"\nDealer's revealed card: {dealerHand[0]}");
        Console.WriteLine($"Dealer's hidden card: ?");

        
        for (int i = 0; i < playerCount; i++)
        {
            Console.WriteLine($"\n--- Player {i + 1}'s Turn ---");
            while (true)
            {
                Console.WriteLine($"Your hand: {string.Join(", ", playerHands[i])} (Total: {CalculateHandValue(playerHands[i])})");
                Console.Write("Would you like to 'hit' or 'stand'? ");
                string choice = Console.ReadLine()?.ToLower();

                if (choice == "hit")
                {
                    playerHands[i].Add(DrawCard());
                    if (CalculateHandValue(playerHands[i]) > 21)
                    {
                        Console.WriteLine($"You busted! Your total is {CalculateHandValue(playerHands[i])}.");
                        break;
                    }
                }
                else if (choice == "stand")
                {
                    playerTotals[i] = CalculateHandValue(playerHands[i]);
                    break;
                }
                else
                {
                    Console.WriteLine("Invalid choice. Please enter 'hit' or 'stand'.");
                }
            }
        }

        
        Console.WriteLine($"\n--- Dealer's Turn ---");
        Console.WriteLine($"Dealer's full hand: {string.Join(", ", dealerHand)} (Total: {CalculateHandValue(dealerHand)})");

        while (CalculateHandValue(dealerHand) < 17)
        {
            string newCard = DrawCard();
            dealerHand.Add(newCard);
            Console.WriteLine($"Dealer hits and draws: {newCard}");
        }

        int dealerTotal = CalculateHandValue(dealerHand);
        Console.WriteLine($"Dealer's final hand: {string.Join(", ", dealerHand)} (Total: {dealerTotal})");

        
        Console.WriteLine("\n--- Results ---");
        for (int i = 0; i < playerCount; i++)
        {
            int playerTotal = CalculateHandValue(playerHands[i]);
            Console.WriteLine($"Player {i + 1}'s hand: {string.Join(", ", playerHands[i])} (Total: {playerTotal})");

            if (playerTotal > 21)
            {
                Console.WriteLine("Result: Busted!");
            }
            else if (dealerTotal > 21 || playerTotal > dealerTotal)
            {
                Console.WriteLine("Result: You win!");
            }
            else if (playerTotal == dealerTotal)
            {
                Console.WriteLine("Result: It's a tie!");
            }
            else
            {
                Console.WriteLine("Result: Dealer wins!");
            }
        }
    }

    static string DrawCard()
    {
        string[] suits = { "♠", "♥", "♦", "♣" };
        string[] ranks = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

        string suit = suits[random.Next(suits.Length)];
        string rank = ranks[random.Next(ranks.Length)];
        return $"{rank}{suit}";
    }

    static int CalculateHandValue(List<string> hand)
    {
        int total = 0;
        int aces = 0;

        foreach (string card in hand)
        {
            string rank = card.Substring(0, card.Length - 1); 
            if (int.TryParse(rank, out int value))
            {
                total += value;
            }
            else if (rank == "A")
            {
                total += 11;
                aces++;
            }
            else
            {
                total += 10; 
            }
        }

        while (total > 21 && aces > 0)
        {
            total -= 10; 
            aces--;
        }

        return total;
    }
}
