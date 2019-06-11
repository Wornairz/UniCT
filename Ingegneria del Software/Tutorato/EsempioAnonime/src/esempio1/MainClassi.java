package esempio1;

class PrintLowerCase implements PrintMode{

	@Override
	public void print(String message) {
		System.out.println(message.toLowerCase());		
	}
}

class PrintUpperCase implements PrintMode{

	@Override
	public void print(String message) {
		System.out.println(message.toUpperCase());		
	}
}
	
public class MainClassi {

	public static void main(String[] args) {
		HelloWorld hw = new HelloWorld();
		hw.printHelloWorld(new PrintLowerCase());
		hw.printHelloWorld(new PrintUpperCase());
	}

	

}
