import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class MeinFeuer {
	private static List<MeinWort> meinworten = new ArrayList<MeinWort>();
	private static int number_of_worten;

	public MeinFeuer() {}
	
	public int getNumberOfWorten() {
		return number_of_worten;
	}
	
	public List<MeinWort> getMeinWorten() {
		return meinworten;
	}
	
	public void setNumberOfWorten(int size) {
		number_of_worten = size;
	}
	
	public void printWortAtPosition(int position) {
		/*
		 * Print function to show the Wort (word,determinant,meaning,topic) at a certain position
		 */
		meinworten.get(position).printWort();
	}
	
	public void loadData(int topic) throws IOException {
		/*
		 * Load data from a the file containing the information of the selected topic. If the filename="0", 
		 * means the user entered 0 or another option not available, and so the application does not load any data and exits.
		 * Otherwise, the program reads line by line the file, assuming the file contains the information of all the worts of the 
		 * topic, one wort per line, with each attribute separated by a comma and without spaces. Example of a line: 
		 * "Zahn,der,tooth,body". Each Wort read is added to the List of MeinWort. Finally, it updates the number_of_worten.
		 */
		String filename = getTopicFile(topic);
		
		if (filename != "0") {
			System.out.println("Loading topic...\n");
			
			File file = new File(getTopicFile(topic));
			BufferedReader br = new BufferedReader(new FileReader(file));
			
			String line;
			int line_count = 0;
			
			while ((line = br.readLine()) != null) {
				line_count++;
				String worten[] = line.split(",");
				MeinWort mw = new MeinWort(worten[0], worten[1], worten[2], worten[3]);
				meinworten.add(mw);
				System.out.print(meinworten.get(line_count-1).getWord() + " - ");
			}
			
			System.out.println("We found " + line_count + " words.");
			number_of_worten = line_count;
			
		} 
		else {
			System.out.println("Closing the application...");
			System.exit(0);
		}
		
	}
	
	public String getTopicFile(int topic) {
		/*
		 * Return the name of the file corresponding to the selected topic.
		 */
		switch(topic) {
			case 1: return "food.txt";
			case 2: return "animals.txt";
			case 3: return "body.txt";
			default: return "0";
		}
	}
	
	public int playGame() {
		/*
		 * Play the game, questioning all the MeinWort (we assume previously loaded) in a random order. For each question, the 
		 * user is asked to answer the correct determinant and the meaning of the word in english. An answer is considered
		 * correct if both answers are right. When not correct, the application prints the correct answer for any wrong answer.
		 * Once all the words have been questioned, it prints the final scores and returns the number of correct answers.
		 */
		System.out.println("Starting the game...");
		
		int size = number_of_worten;
		int[] question_number = new int[size];
		question_number = initializeQuestions(size);
		question_number = shuffleQuestions(question_number, size);
		
		int question = 1;
		int points = 0;
		
		for (int q=0; q<size; q++) {
			String word = meinworten.get(question_number[q]).getWord();
			System.out.println("QUESTION " + question + ": " + word);
			printDeterminants();
			
			Scanner scan = new Scanner(System.in);
			String det = scan.nextLine();
			det = determineDeterminant(det);
			
			System.out.println("Meaning?");
			String meaning = scan.nextLine();
			
			System.out.println("Your answer: -" + det + " " + meaning + "-");
			
			if (det.equals(meinworten.get(question_number[q]).getDeterminant()) && meaning.equals(meinworten.get(question_number[q]).getMeaning())) {
				System.out.println("That is correct!");
				points++;
			}
			else {
				if (!det.equals(meinworten.get(question_number[q]).getDeterminant()))
					System.out.println("Nein! The answer is " + meinworten.get(question_number[q]).getDeterminant());
				if (!meaning.equals(meinworten.get(question_number[q]).getMeaning()))
					System.out.println("Nein! It means " + meinworten.get(question_number[q]).getMeaning());
			}
			question++;
		}
		
		printScores(points, size);
		
		return points;
	}
	
	public int[] initializeQuestions(int size) {
		/*
		 * Initialize an array with size items and containing the numbers 0 to size in ascending order.
		 */
		int[] qn = new int[size];
		for (int i=0; i<size; i++) {
			qn[i] = i;
		}
		return qn;
	}
	
	public int[] shuffleQuestions(int[] qn, int size) {
		/*
		 * Shuffle the array 'qn' by randomly swaping each position of the array with a random position in the array. Return the
		 * final shuffled array.
		 */
		Random rand = new Random(System.currentTimeMillis());
		for (int i=0; i<size; i++) {
			int random_position = rand.nextInt(size);
			int tmp = qn[i];
			qn[i] = qn[random_position];
			qn[random_position] = tmp;
		}
		return qn;
	}
	
	public void printDeterminants() {
		System.out.println("(a) der");
		System.out.println("(b) die");
		System.out.println("(c) das");
	}
	
	public String determineDeterminant(String det) {
		/*
		 * If the user selects a non-available option for a determinant, the determinant is set to schlecht and the answer
		 * will be finally wrong.
		 */
		if (det.equals("a")) return "der";
		else if (det.equals("b")) return "die";
		else if (det.equals("c")) return "das";
		return "schlecht";
	}
	
	public void printScores(int points, int size) {
		double result = ((double)points)/size;
		System.out.print("Die Ende! Correct answers: " + points + "/" + size);
		System.out.format(" [%.2f]\n", 100*result);
	}
	
	public void saveGame(int points, String filename) throws IOException {
		/*
		 * Save final statistics in file 'filename'. The data stored contains the date, the correct/total questions, the
		 * percentage of correct questions, and the topic of the questions.
		 */
    	DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
    	Date date = new Date();
    	
    	String gamestats = "------";
    	gamestats += dateFormat.format(date) + "\n";
    	String percentage = String.format("%.2f", 100*(double)points/number_of_worten);
    	gamestats += "Score: " + points + "/" + number_of_worten + " [" + percentage + "%]\n";
    	gamestats += "Topic: " + meinworten.get(0).getTopic() + "\n\n\n";
    	
    	FileWriter fw = new FileWriter(filename,true); //the true will append the new data
        fw.write(gamestats);//appends the string to the file
        fw.close();
	}
}
