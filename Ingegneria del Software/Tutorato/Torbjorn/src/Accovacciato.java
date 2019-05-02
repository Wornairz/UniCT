
public class Accovacciato implements Postura {

	@Override
	public void spara() {
		System.out.println("100 danni");

	}

	@Override
	public void impreca() {
		System.out.println("Stupidi elfi!");
	}

	@Override
	public String getNome() {
		return "Accovacciato";
	}

}
