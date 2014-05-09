function drawdashboard()
{
	console.log("Drawing dashboard!");
	drawdashboard1();
	drawdashboard2();
	drawdashboard3();
	drawdashboard4();	
}


function drawdashboard1()
{
	var margin = {top: 120, right: 40, bottom: 40, left: 90},
    width = TotalWidth/2 - margin.left - margin.right,
    height = 668/2 - margin.top - margin.bottom;

	var x = d3.scale.ordinal()
    		.rangeRoundBands([0, width], .1);

	var y = d3.scale.linear()
    		.range([height, 0]);

	var xAxis = d3.svg.axis()
    			.scale(x)
    			.orient("bottom");

	var yAxis = d3.svg.axis()
    			.scale(y)
    			.orient("left")
    			.ticks(10, "hours");

	var svg = d3.select("#homeContent").append("g")
    			.attr("transform", "translate(" + margin.left + "," + margin.top  + ")");

	d3.tsv("lib/data/data1.tsv", type, function(error, data) {
  			x.domain(data.map(function(d) { return d.Type; }));
  			y.domain([0, d3.max(data, function(d) { return d.Mean; })]);

  svg.append("g")
      .attr("class", "x axis")
      .attr("transform", "translate(0," + height + ")")
      .call(xAxis);

  svg.append("g")
      .attr("class", "y axis")
      .call(yAxis)
    .append("text")
      .attr("transform", "rotate(-90) translate(0,-50)")
      .attr("y", 6)
      .attr("dy", ".71em")
      .style("text-anchor", "end")
      .text("Mean time to repair (h)");

  svg.selectAll(".bar")
      .data(data)
    .enter().append("rect")
      .attr("class", "bar")
      .attr("x", function(d) { return x(d.Type); })
      .attr("width", x.rangeBand())
      .attr("y", function(d) { return y(d.Mean); })
      .attr("height", function(d) { return height - y(d.Mean); });

});
}

function type(d) {
  d.Mean = +d.Mean;
  return d;
}


function drawdashboard2()
{
	var dataset = { values: [60, 40] };
	var margin = {top: 70, right: 40, bottom: 70, left: 80},
    width = TotalWidth/2 - margin.left - margin.right,
    height = TotalHeight/2 - margin.top - margin.bottom;
	console.log("TW:"+ TotalWidth+ "W: "+width+" H:"+height);
    radius = Math.min(width, height) / 2;

	var color = new Array();

	color.push("green");
	color.push("red");

	var pie = d3.layout.pie().sort(null);

	var arc = d3.svg.arc().innerRadius(radius - 90).outerRadius(radius - 10);
	
	var svg = d3.select("#homeContent").append("g")
    			.attr("transform", "translate(" + (margin.left + width/2 + TotalWidth/2) + "," + (margin.top+height/2) + ")");

	var path = svg.selectAll("path").data(pie(dataset.values)).enter().append("path")
    .attr("fill", function(d, i) { return color[i]; })
    .attr("d", arc);

	
	svg.append("text")
	  .attr("font-family", "sans-serif")
	  .attr("font-size", "25")
      .attr("transform", function(d) { return "translate(0,0)"; })
      .attr("dy", ".35em")
      .style("text-anchor", "middle")
      .text(function(d) { return dataset.values[0]+"%" });


	svg.append("text").attr("transform","translate(0,"+(height/2+20)+")")
		.attr("font-family", "sans-serif")
	  	.attr("font-size", "16")
		.style("text-anchor", "middle")
		.text("SR Solved within agreed time (%)");
}

function drawdashboard3()
{
	var dataset = { values: [82, 18] };
	var margin = {top: 20, right: 20, bottom: 40, left: 20},
    width = (TotalWidth-60)/2 - margin.left - margin.right,
    height = (TotalHeight-170)/2 - margin.top - margin.bottom;
    radius = Math.min(width, height) / 2;

	var color = new Array();

	color.push("green");
	color.push("red");

	var pie = d3.layout.pie().sort(null);

	var arc = d3.svg.arc().innerRadius(radius - 90).outerRadius(radius - 10);
	
	var svg = d3.select("#ind3").append("g")
    			.attr("transform", "translate(" + (margin.left+width/2) + "," + (margin.top+height/2) + ")");

	var path = svg.selectAll("path").data(pie(dataset.values)).enter().append("path")
    .attr("fill", function(d, i) { return color[i]; })
    .attr("d", arc);

	
	svg.append("text")
	  .attr("font-family", "sans-serif")
	  .attr("font-size", "25")
      .attr("dy", ".35em")
      .style("text-anchor", "middle")
      .text(function(d) { return dataset.values[0]+"%" });


	svg.append("text").attr("transform","translate(0,"+(height/2+15)+")")
		.attr("font-family", "sans-serif")
	  	.attr("font-size", "16")
		.style("text-anchor", "middle")
		.text("Proactive vs Reactive Effort (%)");
}






///
//// Gauge
///


function Gauge(placeholderName, configuration)
{
	this.placeholderName = placeholderName;
	
	var self = this; // for internal d3 functions
	
	this.configure = function(configuration)
	{
		this.config = configuration;
		
		this.config.size = this.config.size * 0.9;
		
		this.config.raduis = this.config.size * 0.97 / 2;
		this.config.cx = this.config.size / 2;
		this.config.cy = this.config.size / 2;
		
		this.config.min = undefined != configuration.min ? configuration.min : 0; 
		this.config.max = undefined != configuration.max ? configuration.max : 100; 
		this.config.range = this.config.max - this.config.min;
		
		this.config.majorTicks = configuration.majorTicks || 5;
		this.config.minorTicks = configuration.minorTicks || 2;
		
		this.config.greenColor 	= configuration.greenColor || "#109618";
		this.config.yellowColor = configuration.yellowColor || "#FF9900";
		this.config.redColor 	= configuration.redColor || "#DC3912";
		
		this.config.transitionDuration = configuration.transitionDuration || 500;
	}
 
	this.render = function()
	{
		this.body = d3.select("#ind4content")
							.append("g")
							.attr("class", "gauge");
							
		
		this.body.append("svg:circle")
					.attr("cx", this.config.cx)
					.attr("cy", this.config.cy)
					.attr("r", this.config.raduis)
					.style("fill", "#ccc")
					.style("stroke", "#000")
					.style("stroke-width", "0.5px");
					
		this.body.append("svg:circle")
					.attr("cx", this.config.cx)
					.attr("cy", this.config.cy)
					.attr("r", 0.9 * this.config.raduis)
					.style("fill", "#fff")
					.style("stroke", "#e0e0e0")
					.style("stroke-width", "2px");
					
		for (var index in this.config.greenZones)
		{
			this.drawBand(this.config.greenZones[index].from, this.config.greenZones[index].to, self.config.greenColor);
		}
		
		for (var index in this.config.yellowZones)
		{
			this.drawBand(this.config.yellowZones[index].from, this.config.yellowZones[index].to, self.config.yellowColor);
		}
		
		for (var index in this.config.redZones)
		{
			this.drawBand(this.config.redZones[index].from, this.config.redZones[index].to, self.config.redColor);
		}
		
		if (undefined != this.config.label)
		{
			var fontSize = Math.round(this.config.size / 9);
			this.body.append("svg:text")
						.attr("x", this.config.cx)
						.attr("y", this.config.cy / 2 + fontSize / 2)
						.attr("dy", fontSize / 2)
						.attr("text-anchor", "middle")
						.text(this.config.label)
						.style("font-size", fontSize + "px")
						.style("fill", "#333")
						.style("stroke-width", "0px");
		}
		
		var fontSize = Math.round(this.config.size / 16);
		var majorDelta = this.config.range / (this.config.majorTicks - 1);
		for (var major = this.config.min; major <= this.config.max; major += majorDelta)
		{
			var minorDelta = majorDelta / this.config.minorTicks;
			for (var minor = major + minorDelta; minor < Math.min(major + majorDelta, this.config.max); minor += minorDelta)
			{
				var point1 = this.valueToPoint(minor, 0.75);
				var point2 = this.valueToPoint(minor, 0.85);
				
				this.body.append("svg:line")
							.attr("x1", point1.x)
							.attr("y1", point1.y)
							.attr("x2", point2.x)
							.attr("y2", point2.y)
							.style("stroke", "#666")
							.style("stroke-width", "1px");
			}
			
			var point1 = this.valueToPoint(major, 0.7);
			var point2 = this.valueToPoint(major, 0.85);	
			
			this.body.append("svg:line")
						.attr("x1", point1.x)
						.attr("y1", point1.y)
						.attr("x2", point2.x)
						.attr("y2", point2.y)
						.style("stroke", "#333")
						.style("stroke-width", "2px");
			
			if (major == this.config.min || major == this.config.max)
			{
				var point = this.valueToPoint(major, 0.63);
				
				this.body.append("svg:text")
				 			.attr("x", point.x)
				 			.attr("y", point.y)
				 			.attr("dy", fontSize / 3)
				 			.attr("text-anchor", major == this.config.min ? "start" : "end")
				 			.text(major)
				 			.style("font-size", fontSize + "px")
							.style("fill", "#333")
							.style("stroke-width", "0px");
			}
		}
		
		var pointerContainer = this.body.append("svg:g").attr("class", "pointerContainer");
		
		var midValue = (this.config.min + this.config.max) / 2;
		
		var pointerPath = this.buildPointerPath(midValue);
		
		var pointerLine = d3.svg.line()
									.x(function(d) { return d.x })
									.y(function(d) { return d.y })
									.interpolate("basis");
		
		pointerContainer.selectAll("path")
							.data([pointerPath])
							.enter()
								.append("svg:path")
									.attr("d", pointerLine)
									.style("fill", "#dc3912")
									.style("stroke", "#c63310")
									.style("fill-opacity", 0.7)
					
		pointerContainer.append("svg:circle")
							.attr("cx", this.config.cx)
							.attr("cy", this.config.cy)
							.attr("r", 0.12 * this.config.raduis)
							.style("fill", "#4684EE")
							.style("stroke", "#666")
							.style("opacity", 1);
		
		var fontSize = Math.round(this.config.size / 10);
		pointerContainer.selectAll("text")
							.data([midValue])
							.enter()
								.append("svg:text")
									.attr("x", this.config.cx)
									.attr("y", this.config.size - this.config.cy / 4 - fontSize)
									.attr("dy", fontSize / 2)
									.attr("text-anchor", "middle")
									.style("font-size", fontSize + "px")
									.style("fill", "#000")
									.style("stroke-width", "0px");
		
		this.redraw(this.config.min, 0);
	}
	
	this.buildPointerPath = function(value)
	{
		var delta = this.config.range / 13;
		
		var head = valueToPoint(value, 0.85);
		var head1 = valueToPoint(value - delta, 0.12);
		var head2 = valueToPoint(value + delta, 0.12);
		
		var tailValue = value - (this.config.range * (1/(270/360)) / 2);
		var tail = valueToPoint(tailValue, 0.28);
		var tail1 = valueToPoint(tailValue - delta, 0.12);
		var tail2 = valueToPoint(tailValue + delta, 0.12);
		
		return [head, head1, tail2, tail, tail1, head2, head];
		
		function valueToPoint(value, factor)
		{
			var point = self.valueToPoint(value, factor);
			point.x -= self.config.cx;
			point.y -= self.config.cy;
			return point;
		}
	}
	
	this.drawBand = function(start, end, color)
	{
		if (0 >= end - start) return;
		
		this.body.append("svg:path")
					.style("fill", color)
					.attr("d", d3.svg.arc()
						.startAngle(this.valueToRadians(start))
						.endAngle(this.valueToRadians(end))
						.innerRadius(0.65 * this.config.raduis)
						.outerRadius(0.85 * this.config.raduis))
					.attr("transform", function() { return "translate(" + self.config.cx + ", " + self.config.cy + ") rotate(270)" });
	}
	
	this.redraw = function(value, transitionDuration)
	{
		var pointerContainer = this.body.select(".pointerContainer");
		
		pointerContainer.selectAll("text").text(Math.round(value));
		
		var pointer = pointerContainer.selectAll("path");
		pointer.transition()
					.duration(undefined != transitionDuration ? transitionDuration : this.config.transitionDuration)
					//.delay(0)
					//.ease("linear")
					//.attr("transform", function(d) 
					.attrTween("transform", function()
					{
						var pointerValue = value;
						if (value > self.config.max) pointerValue = self.config.max + 0.02*self.config.range;
						else if (value < self.config.min) pointerValue = self.config.min - 0.02*self.config.range;
						var targetRotation = (self.valueToDegrees(pointerValue) - 90);
						var currentRotation = self._currentRotation || targetRotation;
						self._currentRotation = targetRotation;
						
						return function(step) 
						{
							var rotation = currentRotation + (targetRotation-currentRotation)*step;
							return "translate(" + self.config.cx + ", " + self.config.cy + ") rotate(" + rotation + ")"; 
						}
					});
	}
	
	this.valueToDegrees = function(value)
	{
		// thanks @closealert
		//return value / this.config.range * 270 - 45;
		return value / this.config.range * 270 - (this.config.min / this.config.range * 270 + 45);
	}
	
	this.valueToRadians = function(value)
	{
		return this.valueToDegrees(value) * Math.PI / 180;
	}
	
	this.valueToPoint = function(value, factor)
	{
		return { 	x: this.config.cx - this.config.raduis * factor * Math.cos(this.valueToRadians(value)),
					y: this.config.cy - this.config.raduis * factor * Math.sin(this.valueToRadians(value)) 		};
	}
	
	// initialization
	this.configure(configuration);	
}


var gauges = [];
			
function createGauge(name, label, min, max)
{
	var config = 
				{
					size: 120,
					label: label,
					min: undefined != min ? min : 0,
					max: undefined != max ? max : 100,
					minorTicks: 5
				}
				
	var range = config.max - config.min;
	config.greenZones = [{ from: 75, to: 100 }];
	config.yellowZones = [{ from: 25, to: 75 }];
	config.redZones = [{ from: 0 , to: 25 }];
	config.size = 257;
				
	gauges[name] = new Gauge(name + "GaugeContainer", config);
	gauges[name].render();
}
			
function createGauges()
{
	createGauge("ind4", "Performance", 0,100);			
}
			
function updateGauges()
{
	for (var key in gauges)
	{
		var value = getRandomValue(gauges[key])
		gauges[key].redraw(value);
	}
}
			
function getRandomValue(gauge)
{
	var overflow = 0; //10;
	return gauge.config.min - overflow + (gauge.config.max - gauge.config.min + overflow*2) *  Math.random();
}
	
var gaugeInterval;
		
function drawdashboard4()
{
	createGauges();
	gaugeInterval=setInterval(updateGauges,2000);
}
