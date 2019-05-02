
public class Sdraiato implements Postura {

	@Override
	public Postura spara() {
		System.out.println("200 danni");
		return this;
	}

	@Override
	public Postura impreca() {
		System.out.println("Shh... sono concentrato");
		return this;
	}

	@Override
	public Postura up() {
		return new Accovacciato();
	}

	@Override
	public Postura down() {
		return this;
	}

}
