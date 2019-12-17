package metodo;

public class Main {

	public static void main(String[] args) {
		Shared s = new Shared();
		new T1(s).start();
		new T2(s).start();
	}

}
