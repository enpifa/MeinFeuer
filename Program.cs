using System;
using System.IO;

namespace MeinFeuer
{
    class MainClass
    {
        public static int Main(string[] args)
        {
            /*
             * Ask the user to introduce the topic number, read the topic file containing the information, play the game, where the program 
             * asks for words in random order, and save the statistics. When the user selects 0, the method ReadGame is not executed and the 
             * program exits.
             */
            Console.WriteLine("Wilkommen! Choose a topic:");

            MeinFeuer mf = new MeinFeuer();
            mf.PrintMenu();

            Int32 topic = 0;
            try
            {
                Int32.TryParse(Console.ReadLine(), out topic);
                Console.WriteLine("Topic " + topic.ToString() + " selected...");
            }
            catch (IOException e)
            {
                TextWriter errorWriter = Console.Error;
                errorWriter.WriteLine(e.Message);
                errorWriter.WriteLine("Invalid number entered. Select a number from the options list!");
                return 1;
            }

            int read = 1;
            if (topic > 0) read = mf.ReadGame(topic);
            else
            {
                Console.WriteLine("Thank you for your time! Aufwiedersehen :)");
                return 0;
            }

            int score = 0;
            if (read == 0) {
                score = mf.PlayGame();
                mf.SaveGame(score);
            }

            return 0;
        }
    }
}
