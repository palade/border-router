import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Properties;



public class PropertyReader {
	
	private static final String PROPERTIES_PATH = System.getProperty("user.home") + File.separator + "gateway.properties";
	
	public static void main(String[] args){
		
		Properties properties = new Properties();
		
		File file = new File(PROPERTIES_PATH);
		
		try {
			InputStream in = new FileInputStream(file);
			if (in != null) {
				properties.load(in);
		        	in.close();
		        }
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println(properties.getProperty("address"));		
	}
}
