
public class MeinWort {
	private String word = "";
	private String determinant = "";
	private String meaning = "";
	private String topic = "";
	
	public MeinWort() {}
	
	public MeinWort(String newword, String newdet, String newmeaning, String newtopic) {
		word = newword;
		determinant = newdet;
		meaning = newmeaning;
		topic = newtopic;
	}
	
	public String getWord() {
		return word;
	}
	
	public String getDeterminant() {
		return determinant;
	}
	
	public String getMeaning() {
		return meaning;
	}
	
	public String getTopic() {
		return topic;
	}
	
	public void setWord(String newword) {
		word = newword;
	}
	
	public void setDeterminant(String newdet) {
		determinant = newdet;
	}
	
	public void setMeaning(String newmeaning) {
		meaning = newmeaning;
	}
	
	public void setTopic(String newtopic) {
		topic = newtopic;
	}
	
	public void printWort() {
		System.out.println(word + " - " + determinant + " - " + meaning + " - " + topic);
	}
}
