import Chart from 'chart.js/auto';
import {Line } from "react-chartjs-2";
import React, { useState, useEffect } from "react";

function LineChartHum1({data, id}) {
//   let mac = "";
//   if(id===1)
//   { 
//     mac = "AC:0B:FB:CE:AD:1F";
//   }
//   else if(id===2)
//   {
//     mac = "4C:75:25:06:A1:E7";
//   }

  console.log(data); 
  const [chartData, setChartData] = useState({
    labels: [],
    datasets: [],
  });
 
  const [chartOptions, setChartOptions] = useState({});
 
  useEffect(() => {
    console.count("this is HUMIDITY!!!!")
    let today = new Date();
    console.count(today)
    console.count("This is today from HUMIDIITY")
    
    let new_labels = [...chartData.labels]
    if(chartData.labels.length < 15)
    {
      new_labels.push(today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds());
    }
    else
    {
      new_labels.shift();
      new_labels.push(today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds());
    }

    

    setChartData({
      labels: new_labels ,
      datasets: [
        {
          label: "Humidity",
          data: data.reverse(),
          borderColor: "rgb(53, 162, 235)",
          backgroundColor: "rgba(53, 162, 235, 0.4)",
          
        },
      ],
    });
    // setChartOptions({
    //   scales: {
    //         y: {
    //             title: {
    //               display: true,
    //               text: 'Humidity',
    //               font: {
    //                     family: "'Helvetica Neue', 'Helvetica', 'Arial', sans-serif",
    //                     size: 20,
        
    //               },
    //               color: Chart.defaults.color,
    //             },
                
    //         },
    //         x: {
    //             title: {
    //               display: true,
    //               text: 'Time',
    //               font: {
    //                 family: "'Helvetica Neue', 'Helvetica', 'Arial', sans-serif",
    //                 size: 20,
        
    //                   },
    //               color: Chart.defaults.color,
    //             },
                
    //         }
    //   },
      
    //   responsive: true,
    //   plugins: {
    //     legend: {
    //       position: "top",
    //     },
    //     title: {
    //       display: true,
    //       text: "Whom the fuck let the dogs out",
    //       size: 10,
    //     },
    //   },
      
    // });
  }, [data, ]);


  useEffect(() => {
    // setChartData({
    //   labels: ["John", "Kkkkevin", "Geroge", "Micheal", "Oreo"],
    //   datasets: [
    //     {
    //       label: "Whom the fuck let the dogs out",
    //       // data: [12, 55, 34, 120, 720],
    //       data: data,
    //       borderColor: "rgb(53, 162, 235)",
    //       backgroundColor: "rgba(53, 162, 235, 0.4)",
          
    //     },
    //   ],
    // });
    setChartOptions({
      scales: {
            y: {
                title: {
                  display: true,
                  text: '%',
                  font: {
                        family: "'Helvetica Neue', 'Helvetica', 'Arial', sans-serif",
                        size: 20,
        
                  },
                  color: Chart.defaults.color,
                },
                
            },
            x: {
                title: {
                  display: true,
                  text: 'Time',
                  font: {
                    family: "'Helvetica Neue', 'Helvetica', 'Arial', sans-serif",
                    size: 20,
        
                      },
                  color: Chart.defaults.color,
                },
                
            }
      },
      
      responsive: true,
      plugins: {
        legend: {
          position: "top",
        },
        title: {
          display: true,
          text: mac,
          size: 10,
        },
      },
      
    });
  }, []);
 
  return (
     <>
      
     
     <div style={{ position: "relative", margin: "auto", width: "50%"  }}>
       <Line options={chartOptions} data={chartData}  />
    </div>
    
    </>
    
  );
}
 
export default LineChartHum1;