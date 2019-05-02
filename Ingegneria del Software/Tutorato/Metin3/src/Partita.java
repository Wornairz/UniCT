
public class Partita {
	private ListaUtenti lu;
	private Server s;
	private CheatBuster buster;
	
	public Partita(){
		s = new Server(10, Server.Modalità.BattleRoyale);
		lu = new ListaUtenti();
		buster = new CheatBuster();
	}
	public boolean partecipa(Giocatore g, Server.Modalità m) {
		if(s.getMod() == m && buster.check(g) && s.notFull() ) {
			s.addGiocatore();
			lu.giocatori.add(g);
			return true;
		}
		else
			return false;
	}
	
	public void stampaServer() {
		System.out.println(s.toString() + lu.toString());
	}
}
