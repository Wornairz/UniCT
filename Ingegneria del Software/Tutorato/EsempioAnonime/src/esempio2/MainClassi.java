package esempio2;

import java.util.Arrays;

class Sqrt implements Function{

	@Override
	public double calculate(Double d) {
		return Math.sqrt(d);
	}
	
}

class Pow implements Function{

	@Override
	public double calculate(Double d) {
		return Math.pow(d, 2);
	}
	
}

class Cos implements Function{
	
	@Override
	public double calculate(Double d) {
		return Math.cos(d);
	}
	
}

class Sin implements Function{
	
	@Override
	public double calculate(Double d) {
		return Math.sin(d);
	}
	
}

public class MainClassi {

	public static void main(String[] args) {
		Plotter pl = new Plotter(Arrays.asList(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0));
		pl.plot(new Sqrt());
		pl.plot(new Pow());
		pl.plot(new Cos());
		pl.plot(new Sin());
	}

}
