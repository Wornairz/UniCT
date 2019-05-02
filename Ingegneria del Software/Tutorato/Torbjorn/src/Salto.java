
public class Salto implements Postura {

	@Override
	public void spara() {
		System.out.println("NON POSSO SPARARE MENTRE SALTO!");
	}

	@Override
	public void impreca() {
		System.out.println("TOGLIETEVI DI TORNO ORECCHIE A PUNTA! VI AMMAZZO TUTTI!");
	}

	@Override
	public String getNome() {
		return "Salto";
	}

}
