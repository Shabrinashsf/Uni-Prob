import java.awt.image.*;
import javax.imageio.*;
import java.io.*;

public class ImageFileManager {
    private static final String IMAGE_FORMAT = "jpg";
    
    public static OFImage loadImage(File imageFile){
        try {
            BufferedImage image = ImageIO.read(imageFile);
            if(image == null || (image.getWidth(null) < 0)) {
                return null;
            }
            return new OFImage(image);
        }
        catch(IOException exc) {
            return null;
        }
    }
    
    public static void saveImage(OFImage image, File file){
        try {
            ImageIO.write(image, IMAGE_FORMAT, file);
        }
        catch(IOException exc){
            return;
        }
    }
}