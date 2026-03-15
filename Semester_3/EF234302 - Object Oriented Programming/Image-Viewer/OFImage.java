import java.awt.*;
import java.awt.image.*;
import javax.swing.*;

public class OFImage extends BufferedImage {
    public OFImage(BufferedImage image){
        super(image.getColorModel(), image.copyData(null), 
        image.isAlphaPremultiplied(), null);
    }
    
    public OFImage(int width, int height) {
        super(width, height ,TYPE_INT_RGB);
    }
    
    public void setPixel(int x, int y, Color col){
        int pixel = col.getRGB();
        setRGB(x, y, pixel);
    }
    
    public Color getPixel(int x, int y){
        int pixel = getRGB(x, y);
        return new Color(pixel);
    }
    
    public void darker(){
        int height = getHeight();
        int width = getWidth();
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                setPixel(x, y, getPixel(x,y).darker());
            }
        }
    }
    
    public void lighter(){
        int height = getHeight();
        int width = getWidth();
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                setPixel(x, y, getPixel(x,y).brighter());
            }
        }
    }
    
    public void threshold(){
        int height = getHeight();
        int width = getWidth();
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                Color pixel = getPixel(x,y);
                int brightness = (pixel.getRed() + pixel.getBlue() + pixel.getGreen());
                
                if(brightness <= 85){
                    setPixel(x, y, Color.BLACK);
                } else if(brightness <= 170) {
                    setPixel(x, y, Color.GRAY);
                } else {
                    setPixel(x, y, Color.WHITE);
                }
            }
        }
    }
}