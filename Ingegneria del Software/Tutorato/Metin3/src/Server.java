
public class Server {
	private int capienzaMax;
	private int n_giocatori;
	public static enum Modalità{ BattleRoyale, DeathMatch, EscortThePayload, CaptureTheFlag, CoOp};
	private Modalità mod;
	
	public Server(int capienzaMax, Modalità mod) {
		this.capienzaMax = capienzaMax;
		n_giocatori = 0;
		this.mod = mod;
	}
	
	public void addGiocatore() {
		n_giocatori++;
	}
	
	public Modalità getMod() {
		return mod;
	}
	
	public boolean notFull() {
		return n_giocatori <= capienzaMax; 
	}
	
	@Override
	public String toString() {
		String output = "";
		output += "Capienza Max = " + capienzaMax + "\n";
		output += "Numero di giocatori = " + n_giocatori + "\n";
		output += "Modalità = " + mod + "\n";
		return output;		
	}
}
