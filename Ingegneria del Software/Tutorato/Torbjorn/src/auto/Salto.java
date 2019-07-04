package auto;

public class Salto implements Postura {

	@Override
	public Postura spara() {
		System.out.println("NON POSSO SPARARE MENTRE SALTO!");
		return new InPiedi();
	}

	@Override
	public Postura impreca() {
		System.out.println("TOGLIETEVI DI TORNO ORECCHIE A PUNTA! VI AMMAZZO TUTTI!");
		return new InPiedi();
	}

	@Override
	public Postura up() {
		System.out.println("AAAAARGHHH");
		return new Sdraiato();
	}

	@Override
	public Postura down() {
		return new InPiedi();
	}

}
