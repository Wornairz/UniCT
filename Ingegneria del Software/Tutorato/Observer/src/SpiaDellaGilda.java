import java.util.List;

enum TipoEroe {GUERRIERO, MAGO, LADRO};
public class SpiaDellaGilda implements Spia {
	List<Eroe> targets;
	TipoEroe tipo;
	Taverna t;

	
	public SpiaDellaGilda(TipoEroe tipo, Taverna t) {
		this.tipo = tipo;
		this.t = t;
	}
	
	
	public boolean valutaEroe(Eroe eroe) {
		return eroe.tipo == this.tipo;		
	}
	
	@Override
	public void eroeEntrato() { //update()
		if(valutaEroe(t.getEroe())) targets.add(t.getEroe());		
	}

}
