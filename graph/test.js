var highAverage = 77,
    lowAverage = 58;

$("#container").dxChart({
    dataSource: dataSource.js,
    commonSeriesSettings: {
        argumentField: "day",
        valueField: 'temperature',
        type: "bar"
    },
    palette: 'soft',
    customizePoint: function() {
        if(this.value > highAverage) {
            return { color: '#ff4500', hoverStyle: { color: '#ff4500' } };
        } else if(this.value < lowAverage) {
            return { color: '#00ced1', hoverStyle: { color: '#00ced1' } };
        }
    },
    customizeLabel: function() {
        if (this.value > highAverage) {
            return {
                visible: true,
                backgroundColor: '#ff4500',
                customizeText: function () {
                    return this.valueText + '&#176F'
                }
            }
        }
    },
    valueAxis: {
        min: 40,
        maxValueMargin: 0.1,
        label: {
            customizeText: function() {
                return this.valueText + '&#176F'
            }
        },
        constantLines: [{
            label: {
                text: 'Low Average'
            },
            width: 2,
            value: lowAverage,
            color: '#00ced1',
            dashStyle: 'dash'
        }, {
            label: {
                text: 'High Average'
            },
            width: 2,
            value: highAverage,
            color: '#ff4500',
            dashStyle: 'dash'
        }]
    },
    series: [{}],
    title: {
        text: "Daily Temperature in May"
    },
    legend: {
        visible: false
    }
});