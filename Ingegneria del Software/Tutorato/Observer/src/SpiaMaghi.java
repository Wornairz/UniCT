import java.util.List;

public class SpiaMaghi implements Spia {
	List<Eroe> targets;
	TipoEroe tipo;
	Taverna t;

	
	public SpiaMaghi(TipoEroe tipo, Taverna t) {
		this.tipo = tipo;
		this.t = t;
	}
	
	
	public boolean valutaEroe(Eroe eroe) {
		return eroe.tipo == this.tipo;		
	}
	
	@Override
	public void eroeEntrato() { //update()
		if(valutaEroe(t.getEroe())) targets.add(t.getEroe());
		if(t.getEroi().size() == 10) System.out.println("10 eroi sono entrati");
	}

}
