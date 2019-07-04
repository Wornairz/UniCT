package auto;

public class InPiedi implements Postura{

	@Override
	public Postura spara() {
		System.out.println("50 danni");
		return this;		
	}

	@Override
	public Postura impreca() {
		System.out.println("Maledetti orecchie a punta!");
		return this;
	}

	@Override
	public Postura up() {
		return new Salto();
	}

	@Override
	public Postura down() {
		return new Accovacciato();
	}

}
