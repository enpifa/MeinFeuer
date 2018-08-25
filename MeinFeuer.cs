using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace MeinFeuer
{
    public class MeinFeuer
    {
        List<MeinWort> meinworten = new List<MeinWort>();
        int number_of_worten;

        public MeinFeuer() { number_of_worten = 0; }

        public void AddMeinWort(MeinWort mw) {
            meinworten.Add(mw);
            number_of_worten++;
        } 

        public void AddMeinWort(string w, string d, string m, string t) {
            meinworten.Add(new MeinWort(w, d, m, t));
            number_of_worten++;
        }

        public MeinWort AtIndex(int i) {
            if (i >= number_of_worten) {
                Console.WriteLine("Index out of bounds!");
                throw new System.ArgumentException("Index out of bounds", "i");
            }
            return meinworten[i];
        }

        public int GetNumberWorten() {
            return number_of_worten;
        }

        public void PrintMenu()
        {
            /* Print the topic options */
            Console.WriteLine("(1) Body");
            Console.WriteLine("(2) Food");
            Console.WriteLine("(3) Animals");
            Console.WriteLine("(0) Exit");
        }

        public int ReadGame(Int32 topic) {
            /*
             * Read the file containing the information from the topic. When the filename is schlecht, it means the user selected 
             * an unavailable option, and the method returns 1. It assumes the file contains the information, with a MeinWort per line, 
             * with 'word,determinant,meaning, topic' forming the MeinWort. These attributes are written one per line, separated by 
             * a comma without spacing. An example of a line in the file would be: 'Zahn,der,tooth,body'. Finally, print the number 
             * of lines read and return 0.
             */
            string filename = GetTopicFile(topic);
            if (filename != "schlecht") {
                string[] lines = System.IO.File.ReadAllLines(@filename);
                foreach (string line in lines)
                {
                    string[] worten = line.Split(',');
                    AddMeinWort(new MeinWort(worten[0], worten[1], worten[2], worten[3]));
                }
            }
            else {
                Console.WriteLine("The topic selected does not exist, sorry!");
                return 1;
            }
            Console.WriteLine("Words read: " + number_of_worten);
            return 0;
        }

        private void PrintDeterminants() {
            /* Print the determinant options */
            Console.WriteLine("(a) der");
            Console.WriteLine("(b) die");
            Console.WriteLine("(c) das");
        }

        private string DetermineDeterminant(string det) {
            /* Convert the user answer into the right option for comparison. If the user does not select any of the three options (a,b,c), 
            the determinant is considered wrong, and is assigned the value 'schlecht'. */
            switch (det) {
                case "a": return "der";
                case "b": return "die";
                case "c": return "das";
                default: return "schelecht";
            }
        }

        public int PlayGame() {
            /*
             * First, create an array that contains the number of question to display randomly. Then, for each Wort in the topic, ask for 
             * the determinant and the meaning. An answer is considered correct if both determinant and meaning are correct, and then the
             * score is updated. If not, the method displays whichever wrong answer with the correct one. When all the Worts have been asked,
             * the method displays the final score.
             */
            Console.WriteLine("Let's go!\n");

            int[] question_number = new int[number_of_worten];
            question_number = InitializeQuestions(question_number);
            question_number = ShuffleQuestions(question_number);

            int score = 0;
            int question = 1;

            foreach (int q in question_number) {
                Console.WriteLine("QUESTION " + question + ": " + meinworten[q].getWord());
                PrintDeterminants();

                string determinant = Console.ReadLine();
                determinant = DetermineDeterminant(determinant);

                Console.WriteLine("Meaning?");
                string meaning = Console.ReadLine();
                Console.WriteLine("Your answer: -" + determinant + "-" + meaning + "-");

                if (determinant == meinworten[q].getDeterminant() && meaning == meinworten[q].getMeaning()) {
                    score++;
                    Console.WriteLine("That is correct!");
                } 
                else {
                    if (determinant != meinworten[q].getDeterminant()) Console.WriteLine("Nein! The right determinant is " + meinworten[q].getDeterminant());
                    if (meaning != meinworten[q].getMeaning()) Console.WriteLine("Nein! It means " + meinworten[q].getMeaning());
                }
                question++;
                Console.WriteLine("\n");
            }
            double percentage = (double)score / number_of_worten;
            Console.WriteLine("Your final score: " + score + "/" + number_of_worten + String.Format(" [{0:P2}]", (double)score/(double)number_of_worten));
            return score;
        }

        public void SaveGame(int score) {
            /* 
             * Save the date, score and topic played in a file named scores.txt. If the file does not exist, it is created. Otherwise, 
             * it appends the scores.
             */
            string scores = "\n-------------" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "\n";
            scores += score.ToString() + "/" + number_of_worten.ToString() + String.Format(" [{0:P2}]", (double)score / (double)number_of_worten) + "\n";
            scores += "Topic: " + meinworten[0].getTopic() + "\n";
            File.AppendAllText(@"scores.txt", scores + Environment.NewLine);
        }

        private int[] InitializeQuestions(int[] qn) {
            for (int i = 0; i < number_of_worten; i++) qn[i] = i;
            return qn;
        }

        private int[] ShuffleQuestions(int[] qn) {
            /* Method used to shuffle the question number, so every execution of the program displays the questions in a different order. */
            Random rand = new Random((int)DateTime.Now.Ticks);
            for (int i = 0; i < number_of_worten; i++) {
                int randomNumber = rand.Next(0, number_of_worten);
                int tmp = qn[randomNumber];
                qn[randomNumber] = qn[i];
                qn[i] = tmp;
            }
            return qn;
        }

        private string GetTopicFile(Int32 topic) {
            /* 
             * When the topic does not exist, the method returns schlecht as a filename. The file will not be found, and the application
             * will exit consequently.
             */
            switch (topic) {
                case 1: 
                    return "body.txt";
                case 2:
                    return "food.txt";
                case 3:
                    return "animals.txt";
                default:
                    return "schlecht";
            }
        }
    }
}
