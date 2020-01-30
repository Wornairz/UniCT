
public class MainClass {

	public static void main(String[] args) {
		Shared n = new Shared();
		new T1(n).start();
		new T2(n).start();

	}

}
