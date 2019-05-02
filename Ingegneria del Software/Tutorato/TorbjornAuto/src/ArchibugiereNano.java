
public class ArchibugiereNano {
	private Postura p;
	ArchibugiereNano(){
		p = new InPiedi();
	}
	
	public void fuoco() {
		p.spara();
	}
	
	public void insultaElfo() {
		p.impreca();
	}
	

	public void alza() {
		p = p.up();
	}
	
	public void abbassa() {
		p = p.down();
	}
}
