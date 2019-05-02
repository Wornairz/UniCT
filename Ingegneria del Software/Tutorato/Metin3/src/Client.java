
public class Client {

	public static void main(String[] args) {
		Partita p = new Partita();
		
		Giocatore saro = new Giocatore("SARO");
		saro.addEquip(new Equip(Equip.TipoArma.SparaCoccodrilli));
		saro.addEquip(new Equip(Equip.TipoArma.SparaGalline));
		
		Giocatore dani = new Giocatore("DANILO");
		dani.addEquip(new Equip(Equip.TipoArma.FucileCecchino));
		dani.addEquip(new Equip(Equip.TipoArma.FucilePompa));
		
		Giocatore peppe = new Giocatore("PEPPE");
		peppe.addEquip(new Equip(Equip.TipoArma.Lanciagranate));
		peppe.addEquip(new Equip(Equip.TipoArma.FucileAssalto));

		//Cliente deve conoscere Server... ma questo non rispetta il Façade
		System.out.println(p.partecipa(saro, Server.Modalità.BattleRoyale)); 
		System.out.println(p.partecipa(dani, Server.Modalità.CaptureTheFlag));
		System.out.println(p.partecipa(peppe, Server.Modalità.BattleRoyale));
		
		p.stampaServer();
	}

}
