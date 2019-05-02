

public class CheatBuster {
	public boolean check(Giocatore g) {
		for(Equip e : g.equipaggiamento) {
			if(e.arma == Equip.TipoArma.SparaCoccodrilli || e.arma == Equip.TipoArma.SparaGalline)
				return false;
		}
		return true;
	}
}
