import java.io.File;
import java.util.Scanner;

public class Myclass {
	
	public static void printTopics() {
		System.out.println("Please, choose a topic:");
		System.out.println("(1) Food");
		System.out.println("(2) Animals");
		System.out.println("(3) Body");
		System.out.println("(0) Exit");
	}
	
	public static void main(String[] args) throws Exception {
		System.out.println("Welcome to MeinFeuer!");
		printTopics();
		
		Scanner scan = new Scanner(System.in);
		int topic = Integer.parseInt(scan.nextLine());
		
		MeinFeuer mf = new MeinFeuer();
		mf.loadData(topic);

		int points = mf.playGame();
		
		String filename = "gamescores.txt";
		File file = new File(filename);
        
		if (!file.exists()) {
        	System.out.println("Creating your stats file...");
            file.createNewFile();
        } else {
        	System.out.println("Adding scores to the your stats...");
        }
        
        mf.saveGame(points, filename);
        
        System.out.println("Thank you for playing! Aufwiedersehen :)");

	}
}
