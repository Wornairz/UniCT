package esempio2;

import java.util.Arrays;

public class MainClassiAnonime {

	public static void main(String[] args) {
		Plotter pl = new Plotter(Arrays.asList(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0));
		pl.plot(new Function() {
			
			@Override
			public double calculate(Double d) {
				return Math.sqrt(d);
			}
		});
		pl.plot(new Function() {
			
			@Override
			public double calculate(Double d) {
				return Math.pow(d, 2);
			}
		});
		pl.plot(new Function() {
			
			@Override
			public double calculate(Double d) {
				return Math.sin(d);
			}
		});
		pl.plot(new Function() {
			
			@Override
			public double calculate(Double d) {
				return Math.cos(d);
			}
		});
	}

}
