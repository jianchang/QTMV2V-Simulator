//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2012.09.28 at 03:23:37 PM EDT 
//


package source;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;all>
 *         &lt;element ref="{}MaxDistance"/>
 *         &lt;element ref="{}MultiChannel"/>
 *       &lt;/all>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {

})
@XmlRootElement(name = "SimplePhysModel")
public class SimplePhysModel {

    @XmlElement(name = "MaxDistance", defaultValue = "200.0")
    protected float maxDistance;
    @XmlElement(name = "MultiChannel", required = true, defaultValue = "NO")
    protected String multiChannel;

    /**
     * Gets the value of the maxDistance property.
     * 
     */
    public float getMaxDistance() {
        return maxDistance;
    }

    /**
     * Sets the value of the maxDistance property.
     * 
     */
    public void setMaxDistance(float value) {
        this.maxDistance = value;
    }

    /**
     * Gets the value of the multiChannel property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getMultiChannel() {
        return multiChannel;
    }

    /**
     * Sets the value of the multiChannel property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setMultiChannel(String value) {
        this.multiChannel = value;
    }

}