
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
		switch(p.getNome()) {
		case "InPiedi": p = new Salto(); break;
		case "Accovacciato" : p = new InPiedi(); break;
		case "Sdraiato" : p = new Accovacciato(); break;
		case "Salto" : p = new Sdraiato(); break;
		default: System.out.println("Azione non permessa");
		}
	}
	
	public void abbassa() {
		switch(p.getNome()) {
		case "InPiedi": p = new Accovacciato(); break;
		case "Accovacciato" : p = new Sdraiato(); break;
		case "Salto" : p = new InPiedi(); break;
		case "Sdraiato" : p = new Salto(); break;
		default: System.out.println("Azione non permessa");
		}
	}
}
