//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2012.09.28 at 03:23:37 PM EDT 
//


package source;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
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
 *       &lt;choice>
 *         &lt;group ref="{}NormalGroup"/>
 *         &lt;group ref="{}PoissonGroup"/>
 *         &lt;group ref="{}BernoulliGroup"/>
 *         &lt;group ref="{}BinomialGroup"/>
 *         &lt;group ref="{}UniformGroup"/>
 *         &lt;group ref="{}UserDefineGroup"/>
 *       &lt;/choice>
 *       &lt;attribute ref="{}DistributionType"/>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "normalMean",
    "normalStdev",
    "poissonMean",
    "bernoulliProb",
    "binomialProb",
    "binomialUpBound",
    "uniformUpBound",
    "uniformLowBound",
    "userDefineValue"
})
@XmlRootElement(name = "TrustUp")
public class TrustUp {

    @XmlElement(name = "NormalMean")
    protected Float normalMean;
    @XmlElement(name = "NormalStdev")
    protected Float normalStdev;
    @XmlElement(name = "PoissonMean")
    protected Float poissonMean;
    @XmlElement(name = "BernoulliProb")
    protected Float bernoulliProb;
    @XmlElement(name = "BinomialProb")
    protected Float binomialProb;
    @XmlElement(name = "BinomialUpBound")
    protected Integer binomialUpBound;
    @XmlElement(name = "UniformUpBound")
    protected Float uniformUpBound;
    @XmlElement(name = "UniformLowBound")
    protected Float uniformLowBound;
    @XmlElement(name = "UserDefineValue")
    protected Float userDefineValue;
    @XmlAttribute(name = "DistributionType")
    protected String distributionType;

    /**
     * Gets the value of the normalMean property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getNormalMean() {
        return normalMean;
    }

    /**
     * Sets the value of the normalMean property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setNormalMean(Float value) {
        this.normalMean = value;
    }

    /**
     * Gets the value of the normalStdev property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getNormalStdev() {
        return normalStdev;
    }

    /**
     * Sets the value of the normalStdev property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setNormalStdev(Float value) {
        this.normalStdev = value;
    }

    /**
     * Gets the value of the poissonMean property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getPoissonMean() {
        return poissonMean;
    }

    /**
     * Sets the value of the poissonMean property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setPoissonMean(Float value) {
        this.poissonMean = value;
    }

    /**
     * Gets the value of the bernoulliProb property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getBernoulliProb() {
        return bernoulliProb;
    }

    /**
     * Sets the value of the bernoulliProb property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setBernoulliProb(Float value) {
        this.bernoulliProb = value;
    }

    /**
     * Gets the value of the binomialProb property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getBinomialProb() {
        return binomialProb;
    }

    /**
     * Sets the value of the binomialProb property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setBinomialProb(Float value) {
        this.binomialProb = value;
    }

    /**
     * Gets the value of the binomialUpBound property.
     * 
     * @return
     *     possible object is
     *     {@link Integer }
     *     
     */
    public Integer getBinomialUpBound() {
        return binomialUpBound;
    }

    /**
     * Sets the value of the binomialUpBound property.
     * 
     * @param value
     *     allowed object is
     *     {@link Integer }
     *     
     */
    public void setBinomialUpBound(Integer value) {
        this.binomialUpBound = value;
    }

    /**
     * Gets the value of the uniformUpBound property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getUniformUpBound() {
        return uniformUpBound;
    }

    /**
     * Sets the value of the uniformUpBound property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setUniformUpBound(Float value) {
        this.uniformUpBound = value;
    }

    /**
     * Gets the value of the uniformLowBound property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getUniformLowBound() {
        return uniformLowBound;
    }

    /**
     * Sets the value of the uniformLowBound property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setUniformLowBound(Float value) {
        this.uniformLowBound = value;
    }

    /**
     * Gets the value of the userDefineValue property.
     * 
     * @return
     *     possible object is
     *     {@link Float }
     *     
     */
    public Float getUserDefineValue() {
        return userDefineValue;
    }

    /**
     * Sets the value of the userDefineValue property.
     * 
     * @param value
     *     allowed object is
     *     {@link Float }
     *     
     */
    public void setUserDefineValue(Float value) {
        this.userDefineValue = value;
    }

    /**
     * Gets the value of the distributionType property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getDistributionType() {
        return distributionType;
    }

    /**
     * Sets the value of the distributionType property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setDistributionType(String value) {
        this.distributionType = value;
    }

}
