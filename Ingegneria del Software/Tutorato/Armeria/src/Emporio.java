public class Emporio {
	
	public static Spada compraSpada() {
		return new SpadaBase();
	}
	
	public static Spada compraSpadaPesante() {
		return new SpadaPesante();
	}
	
	public static Spada compraSpadaInfuocata() {
		return new Infuocata(new SpadaBase());
	}

	public static Spada compraSpadaPesanteInfuocata() {
		return new Infuocata(new SpadaPesante());
	}
	
	public static Spada compraSpadaSpettraleInfuocata() {
		return new Spettrale(new Infuocata(new SpadaBase()));
	}

	public static Spada compraSpadaInfuocatissima() {
		return new Infuocata(new Infuocata(new SpadaBase()));
	}
	
	public static Spada compraSpadaInfuocataAvvelenata() {
		return new Avvelenata(new Infuocata(new SpadaBase()));
	}
	
	public static Spada compraSpadaPesanteSpettraleAvvelenata() {
		return new Avvelenata(new Spettrale(new SpadaPesante()));
	}
	
	public static Spada compraSpadaFullOptional() {
		return new Infuocata(new Avvelenata(new Spettrale(new SpadaPesante())));
	}

}