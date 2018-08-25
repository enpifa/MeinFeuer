using System;
namespace MeinFeuer
{
    public class MeinWort
    {
        private string word;
        private string determinant;
        private string meaning;
        private string topic;

        public MeinWort()
        {
            word = "";
            determinant = "";
            meaning = "";
            topic = "";
        }

        public MeinWort(string w, string d, string m, string t) {
            word = w;
            determinant = d;
            meaning = m;
            topic = t;
        }

        public string getWord() { return word; }
        public string getDeterminant() { return determinant; }
        public string getMeaning() { return meaning; }
        public string getTopic() { return topic; }

        public void setWord(string w) { word = w; }
        public void setDeterminant(string d) { determinant = d; }
        public void setMeaning(string m) { meaning = m; }
        public void setTopic(string t) { topic = t; }

    }
}
