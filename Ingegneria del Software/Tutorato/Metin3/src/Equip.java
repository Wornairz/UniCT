
public class Equip {
	public static enum TipoArma {SparaCoccodrilli, FucileAssalto, SparaGalline, FucileCecchino , Lanciagranate , FucilePompa};
	public TipoArma arma;
	public int danno;
	
	public Equip(TipoArma arma){
		this.arma = arma;
		if(arma == TipoArma.SparaCoccodrilli || arma == TipoArma.SparaGalline)
			danno = 100000000;
		else
			danno = 200;
	}
}
