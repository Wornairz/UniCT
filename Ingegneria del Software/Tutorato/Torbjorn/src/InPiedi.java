
public class InPiedi implements Postura{

	@Override
	public void spara() {
		System.out.println("50 danni");
		
	}

	@Override
	public void impreca() {
		System.out.println("Maledetti orecchie a punta!");
		
	}

	@Override
	public String getNome() {
		return "InPiedi";
	}

}
