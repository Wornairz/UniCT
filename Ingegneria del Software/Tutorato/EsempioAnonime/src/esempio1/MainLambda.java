package esempio1;


public class MainLambda {

	public static void main(String[] args) {
		HelloWorld hw = new HelloWorld();
		hw.printHelloWorld(s -> System.out.println(s.toLowerCase()));
		hw.printHelloWorld(s -> System.out.println(s.toUpperCase()));
	}

}
