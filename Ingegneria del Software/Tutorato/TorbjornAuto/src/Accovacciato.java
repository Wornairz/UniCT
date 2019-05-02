
public class Accovacciato implements Postura {

	@Override
	public Postura spara() {
		System.out.println("100 danni");
		return this;
	}

	@Override
	public Postura impreca() {
		System.out.println("Stupidi elfi!");
		return this;
	}

	@Override
	public Postura up() {
		return new InPiedi();
	}

	@Override
	public Postura down() {
		return new Sdraiato();
	}

}
