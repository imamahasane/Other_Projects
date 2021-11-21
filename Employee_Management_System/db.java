
package com.emamahasan;

import java.sql.*;
import javax.swing.*;
import javax.swing.JOptionPane;

public class db 
{   
    Connection conn = null;
    
    static Connection java_db()
    {   
        try
        {            
            Class.forName("org.sqlite.JDBC");
            Connection conn = DriverManager.getConnection("jdbc:sqlite:D:\\Daffodil International University\\NetBeansProjects\\Employee_Payroll_System\\mydatabase.sqlite");
            return conn;                                        
        }
        
        catch (Exception e)
        {
            JOptionPane.showMessageDialog(null, e);
            return null;
        }              
    }
       
}
