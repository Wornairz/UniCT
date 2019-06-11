package esempio1;

public class MainClassiAnonime {

	public static void main(String[] args) {
		HelloWorld hw = new HelloWorld();
		hw.printHelloWorld(new PrintMode() {

			@Override
			public void print(String message) {
				System.out.println(message.toLowerCase());						
			}
			
		});
		hw.printHelloWorld(new PrintMode() {

			@Override
			public void print(String message) {
				System.out.println(message.toUpperCase());						
			}
			
		});
	}

}
