package main;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.logging.Level;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.htmlunit.HtmlUnitDriver;

public class WebScraper {
    static WebDriver driver = new HtmlUnitDriver();
    public static void main(String[] args) {
        //((HtmlUnitDriver) driver).setJavascriptEnabled(true);

        java.util.logging.Logger.getLogger("com.gargoylesoftware").setLevel(Level.OFF);
        
        String csv = "isbns.csv";
        BufferedReader br = null;
        String line = "";
        
        try {
            br = new BufferedReader(new FileReader(csv));
            while ((line = br.readLine()) != null) {
                getInfo(line);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        driver.quit();
        

    }
    
    public static void getInfo(String isbn) {
        driver.get("https://www.amazon.com/Advanced-Search-Books/b/ref=sxts_snpl_1_1_e6ee52b1-5d05-445e-ae1a-ef65db085f87?node=241582011&pd_rd_w=PiOgn&pf_rd_p=e6ee52b1-5d05-445e-ae1a-ef65db085f87&pf_rd_r=H0QHRVYG28F6NG56T7C4&pd_rd_r=d5fea254-d35a-46e8-b2b9-77a6bb5fceba&pd_rd_wg=rLRQ3&qid=1559594852");

        
        WebElement e = driver.findElement(By.name("field-isbn"));
        e.sendKeys(isbn);
        e.submit();

        WebElement we = driver.findElement(By.xpath("/html/body/div[1]/div[2]/div[1]/div[2]/div/span[3]/div[1]/div/div/div/div/div[2]/div[2]/div/div[1]/div/div/div[1]/h2/a/span"));
        String name = we.getText();
        we.click();
        System.out.println("Name of Book: " + name);
        WebElement buyNewPrice = driver.findElement(By.xpath("//*[@id=\"ppdFixedGridRightColumn\"]"));
        String block = buyNewPrice.getText();
        Scanner scan = new Scanner(block);
        while (scan.hasNext()) {
            String current = scan.nextLine();
            if (current.contains("Buy new")) {
                String potentialPrice = scan.nextLine();
                if (potentialPrice.contains("$")) {
                    System.out.println("Price of Book: " + potentialPrice.trim());
                    scan.close();
                    System.out.println("Url: " + driver.getCurrentUrl());
                    return;
                }
            }
        }
        scan.close();
    }
}
